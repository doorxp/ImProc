// ImProc_Filters.c
// Image Processing Library
// Naming Semantics - All methods called from outside the library have leading capital letters
//                    All utility methods called from within the library have leading lowercase letters
//                    Utility methods should generally not be called from outside the library unless the
//                    implementer understands the function usage and memory allocations involved

#include <math.h>
#include "ImProc_Utils.h"
#include "ImProc_Filters.h"

// spatial filter methods
// the kernel must be freed by calling function
kernel_1d Make_Gaussian_1d_Kernel(double sigma)
{
	int i = 0;
	kernel_1d newKernel;

	// create the kernel
	int center = (int) (3.0*sigma);
	int length = 2*center+1;

	double* kernel_d = malloc(length*sizeof(double));
	int* kernel_i = malloc(length*sizeof(int));

	// fill the double kernel
	double sigma2 = sigma * sigma;
	for (i; i < length; i++){
		double r = center - i;
		kernel_d[i] = (double)exp(-0.5 * (r*r) / sigma2);
	}

	// fill the int kernel
	// find min value
	double min;
	min = kernel_d[0];
	for(i = 1; i < length; i++)
		if(kernel_d[i] < min) min = kernel_d[i];

	double coeff = 1.0/min;
	int sum = 0;
	for(i = 0; i < length; i++)
	{
		kernel_i[i] = (int)(kernel_d[i] * coeff);
		sum += kernel_i[i];
	}

	newKernel.kernel_int = kernel_i;
	newKernel.kernel_double = kernel_d;
	newKernel.sum = sum;
	newKernel.length = length;

	return newKernel;
}

pixel* Gaussian_Blur(pixel* image, double sigma, int width, int height, int dtype, pixel* output)
{
	// compute the kernel
	kernel_1d kernel = Make_Gaussian_1d_Kernel(sigma);

	// if float computation then normalize kernel
	if(dtype == FLOAT)
	{
		double sum = 0;
		int i = 0;
		for(i; i < kernel.length; i++)
		{
			sum += kernel.kernel_double[i];
		}
		for(i = 0; i < kernel.length; i++)
		{
			kernel.kernel_double[i] = kernel.kernel_double[i]/sum;
		}
	}

	// create pixelInt array for convolution
	pixelInt* cimage = pixel_to_pixelInt(image, width, height, NULL);

	// convolve
	convolve_in_X(cimage, kernel, width, height, dtype);
	convolve_in_Y(cimage, kernel, width, height, dtype);

	// convert back to pixel arrray
	pixelInt_to_pixel(cimage, width, height, output);

	// free the kernel pointers and pixelInt image
	free(kernel.kernel_double);
	free(kernel.kernel_int);
	free(cimage);

	return output;
}

pixel* Blur_Or_Sharpen(pixel* image, float w, int width, int height, int type, pixel* output)
{
	// w must be between -1 and 1
	if(w < -1 || w > 1)
		return NULL;

	// build box filter kernel
	int box_filter[5] = {1, 1, 1, 1, 1};
	kernel_1d box_kernel;
	box_kernel.kernel_int = box_filter;
	box_kernel.length = 5;
	box_kernel.sum = 5;

	// build pixelInt array from image so we can work outside char bounds
	pixelInt* image1 = pixel_to_pixelInt(image, width, height, NULL);
	pixelInt* image2 = pixel_to_pixelInt(image, width, height, NULL);

	pixelInt_pointOp(image1, 1+w, width, height, 2);

	// convolve
	convolve_in_X(image2, box_kernel, width, height, type);
	convolve_in_Y(image2, box_kernel, width, height, type);

	pixelInt_pointOp(image2, w, width, height, 2);
	pixelInt_combine(image1, image2, width, height, 1);
	pixelInt_to_pixel(image1, width, height, output);

	// free the kernel pointers, int arrays
	free(image1);
	free(image2);

	return output;
}

// use floating convolution with 1d box filter to speed up blurring
pixel* Fast_Blur(pixel* image, int size, int width, int height, pixel* output)
{
	int length = width * height;

	// create two copies of int array for convolution
	int* intImage = RGB_to_Gray_IntArray(image, width, height, NULL);
	int* intCopy = malloc(length * sizeof(int));
	memcpy(intCopy, intImage, length*sizeof(int));

	// convolve in X
	int r = size/2;
	int w = width - 2 * r;
	int i, j, k;

	// use int convolution for faster results but some slight data loss
	int* sums = malloc(size * sizeof(int));
	int sum = 0;

	for(j = 0; j < height; j++)
	{
		for(i = -r; i < width-r; i++)
		{
			int l = ((i + w) % w);
			sum = 0;
			for(k = -r; k <= r; k++)
			{
				int val = *(intCopy+(j*width)+l+k+r);
				sum += val;
			}

			// store the results to intermediate array
			int offset = (j*width+i+r);
			intImage[offset] = ((float)sum)/size;
		}
	}

	// convolve in Y
	w = height - 2 * r;

	for(i = 0; i < width; i++)
	{
		for(j = -r; j < height-r; j++)
		{
			int l = ((j + w) % w);
			sum = 0;
			for(k = -r; k <= r; k++)
			{
				int val = *(intImage+i+(width*(l+k+r)));
				sum += val;
			}

			// store the results to intermediate array
			int offset = width*(j+r)+(i);
			intCopy[offset] = ((float)sum)/size;
		}
	}

	IntArray_to_PixelArray(intCopy, width, height, output);
	free(intImage);
	free(intCopy);
	free(sums);
	return output;
}

pixel* Fast_Sharpen(pixel* image, int width, int height, pixel* output)
{
	int i = 0;
	int length = width * height;

	// build box filter kernel
	int laplacian [3] = {1, -2, 1};
	kernel_1d sharpen_kernel;
	sharpen_kernel.kernel_int = laplacian;
	sharpen_kernel.length = 3;
	sharpen_kernel.sum = 0;

	// create copy for convolution
	pixelInt* image1 = pixel_to_pixelInt(image, width, height, NULL);
	pixelInt* image2 = pixel_to_pixelInt(image, width, height, NULL);

	// convolve
	convolve_in_X(image2, sharpen_kernel, width, height, 1);
	convolve_in_Y(image2, sharpen_kernel, width, height, 1);

	pixelInt_combine(image1, image2, width, height, SUB);
	pixelInt_to_pixel(image1, width, height, output);

	free(image1);
	free(image2);

	return output;
}


pixel* Unsharp_Masking(pixel* image, float sigma, float w, int width, int height, int type, pixel* output)
{
	// w must be between 0 and 1
	if(w < 0 || w > 1)
		return NULL;

	// compute the kernel
	kernel_1d kernel = Make_Gaussian_1d_Kernel(sigma);

	// if float computation then normalize kernel
	if(type == FLOAT)
	{
		double sum = 0;
		int i = 0;
		for(i; i < kernel.length; i++)
		{
			sum += kernel.kernel_double[i];
		}
		for(i = 0; i < kernel.length; i++)
		{
			kernel.kernel_double[i] = kernel.kernel_double[i]/sum;
		}
	}

	// build pixelInt array from image so we can work outside char bounds
	pixelInt* image1 = pixel_to_pixelInt(image, width, height, NULL);
	pixelInt* image2 = pixel_to_pixelInt(image, width, height, NULL);

	pixelInt_pointOp(image1, 1+w, width, height, 2);

	// convolve
	convolve_in_X(image2, kernel, width, height, type);
	convolve_in_Y(image2, kernel, width, height, type);

	pixelInt_pointOp(image2, w, width, height, 2);
	pixelInt_combine(image1, image2, width, height, 1);
	pixelInt_to_pixel(image1, width, height, output);

	// free the kernel pointers, int arrays
	free(kernel.kernel_int);
	free(kernel.kernel_double);
	free(image1);
	free(image2);

	return output;
}
