// ImProc_Edges.c
// Image Processing Library
// Naming Semantics - All methods called from outside the library have leading capital letters
//                    All utility methods called from within the library have leading lowercase letters
//                    Utility methods should generally not be called from outside the library unless the
//                    implementer understands the function usage and memory allocations involved

#include <math.h>
#include <stdlib.h>
#include "ImProc_Convolve.h"
#include "ImProc_Utils.h"
#include "ImProc_Edges.h"
#include "ImProc_Filters.h"

// edge detection
pixel* Gradient_Magnitude(pixel* image, double sigma, int width, int height, pixel* output)
{
  int i = 0;
  int length = width * height;

  // compute the kernel
  kernel_1d g_kernel = Make_Gaussian_1d_Kernel(sigma);

  // build derivative kernel
  int derivative [3] = {1, 0, -1};
  kernel_1d d_kernel;
  d_kernel.kernel_int = derivative;
  d_kernel.length = 3;
  // this is not technically the sum but we want to normalize by 1/2
  d_kernel.sum = 2;

  // create copy for convolution
  pixelInt* image1 = pixel_to_pixelInt(image, width, height, NULL);
   
  // convolve in X
  convolve_in_X(image1, g_kernel, width, height, INT);
  convolve_in_Y(image1, g_kernel, width, height, INT);

  pixelInt* image2 = pixelInt_copy(image1, width, height);
  convolve_in_X(image1, d_kernel, width, height, INT);
  convolve_in_Y(image2, d_kernel, width, height, INT);

  pixelInt_pointOp(image1, 0.0, width, height, SQR);
  pixelInt_pointOp(image2, 0.0, width, height, SQR);

  pixelInt_combine(image1, image2, width, height, ADD);
  pixelInt_pointOp(image1, 0.0, width, height, SQRT);

  pixelInt_to_pixel(image1, width, height, output);
  Threshold(output, 5, width, height, output);
  
  // free memory
  free(image1);
  free(image2);

  return output;
}

pixel* Fast_Edges(pixel* image, int blur_size, int threshold, int width, int height, pixel* output)
{
	int i;
	int length = width * height;

	// build derivative kernel
	int derivative [3] = {1, 0, -1};
	kernel_1d d_kernel;
	d_kernel.kernel_int = derivative;
	d_kernel.length = 3;
	// this is not technically the sum but we want to normalize by 1/2
	d_kernel.sum = 2;

	// blur kernel using fast blur method
	Fast_Blur_Gray(image, blur_size, width, height, output);

	// convert to int array for fast grayscale convolution
	int* image1 = RGB_to_Gray_IntArray(output, width, height, NULL);
	int* image2 = malloc(length * sizeof(int));
	memcpy(image2, image1, length*sizeof(int));

	// convolve with derivative kernel
	gray_convolve_in_X(image1, d_kernel, width, height);
	gray_convolve_in_Y(image2, d_kernel, width, height);

	// square images
	for(i = 0; i < length; i++)
	{
		image1[i] = pow(image1[i], 2);
		image2[i] = pow(image2[i], 2);
	}

	// combine x/y gradient
	for(i = 0; i < length; i++)
	{
		image1[i] += image2[i];
		image1[i] = sqrt(image1[i]);
	}

	// convert back to pixel array
	IntArray_to_PixelArray(image1, width, height, output);

	Threshold(output, threshold, width, height, output);

	// free allocated memory
	free(image1);
	free(image2);

	return output;
}

pixel* Test_Edges(pixel* image, int threshold, int width, int height, pixel* output)
{
	int i, j, a, b, sum;
	int length = width * height;
	short quick_mask[3][3] =  {
       {-1,  0, -1},
       { 0,  4,  0},
       {-1,  0, -1} };

	RGB_to_Gray_PixelArray(image, width, height, image);

	for(i=1; i<height-1; i++){
      for(j=1; j<width-1; j++){
         sum = 0;
         for(a=-1; a<2; a++){
            for(b=-1; b<2; b++){
               sum = sum + image[(i*width)+(a*width)+j+b].red * quick_mask[a+1][b+1];
            }
         }
         if(sum < 0)   sum = 0;
         if(sum > 255) sum = 255;
         
		 pixel newPixel;
		 newPixel.red = newPixel.green = newPixel.blue = sum;
		 newPixel.alpha = 255;
		 output[i*width + j] = newPixel;

      }  /* ends loop over j */
   }  /* ends loop over i */

	// threshold
	Threshold(output, threshold, width, height, output);

	return output;
}