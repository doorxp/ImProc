// ImProc_convolve.c
// Image Processing Library
// Naming Semantics - All methods called from outside the library have leading capital letters
//                    All utility methods called from within the library have leading lowercase letters
//                    Utility methods should generally not be called from outside the library unless the
//                    implementer understands the function usage and memory allocations involved

#include <math.h>
#include <stdlib.h>
#include "ImProc_Base.h"
#include "ImProc_Convolve.h"

// convolution methods
pixelInt* convolve_in_X(pixelInt* image, kernel_1d kernel, int width, int height, int d_type)
{
  // need to make duplicate image
  pixelInt* copy = pixelInt_copy(image, width, height);
  int length = width * height;
  int r = kernel.length/2;
  int w = width - 2 * r;
  int i, j, k;

  // use float convolution for precise, non real-time processing
  if(d_type == FLOAT)
    {
      double rsum, gsum, bsum, red, green, blue;

      for(j = 0; j < height; j++)
	{
	  for(i = -r; i < width-r; i++)
	    {
	      int l = ((i + w) % w);
	      rsum = 0;
	      gsum = 0;
	      bsum = 0;
	      for(k = -r; k <= r; k++)
		{
		  pixelInt p = *(copy+(j*width)+l+k+r);
		  red = p.red;
		  green = p.green;
		  blue = p.blue;

		  // double p = copy.getf(l+k+r,j);
		  rsum += red * kernel.kernel_double[k+r];
		  gsum += green * kernel.kernel_double[k+r];
		  bsum += blue * kernel.kernel_double[k+r];
		}
	      
	      pixelInt p;

	      // round floats
	      p.red = (int)rsum;
	      p.green = (int)gsum;
	      p.blue = (int)bsum;

	      *(image+(j*width)+(i+r)) = p;
	    }
	}
    }

  // use int convolution for faster results but some slight data loss
  else
    {
      int rsum, gsum, bsum, red, green, blue;

      for(j = 0; j < height; j++)
	{
	  for(i = -r; i < width-r; i++)
	    {
	      int l = ((i + w) % w);
	      rsum = 0;
	      gsum = 0;
	      bsum = 0;
	      for(k = -r; k <= r; k++)
		{
		  pixelInt p = *(copy+(j*width)+l+k+r);
		  red = p.red;
		  green = p.green;
		  blue = p.blue;

		  rsum += red * kernel.kernel_int[k+r];
		  gsum += green * kernel.kernel_int[k+r];
		  bsum += blue * kernel.kernel_int[k+r];
		}

	      // store the results to intermediate array
	      int offset = (j*width+i+r);
	      image[offset].red = rsum;
	      image[offset].green = gsum;
	      image[offset].blue = bsum;
	    }
	}

      // normalize results if kernel sum != 0
      if(kernel.sum != 0)
	{
	  for(i = 0; i < length; i++)
	    {
	      // normalize values
	      image[i].red = ((float)image[i].red)/kernel.sum;
	      image[i].green = ((float)image[i].green)/kernel.sum;
	      image[i].blue = ((float)image[i].blue)/kernel.sum;
	    }
	}
    }
  free(copy);
}

pixelInt* convolve_in_Y(pixelInt* image, kernel_1d kernel, int width, int height, int d_type)
{
  // need to make duplicate image
  pixelInt* copy = pixelInt_copy(image, width, height);
  int length = width * height;
  int r = kernel.length/2;
  int w = height - 2 * r;
  int i, j, k;

  if(d_type == FLOAT)
    {
      double rsum, gsum, bsum, red, green, blue;

      for(i = 0; i < width; i++)
	{
	  for(j = -r; j < height-r; j++)
	    {
	      int l = ((j + w) % w);
	      rsum = 0.0;
	      gsum = 0.0;
	      bsum = 0.0;
	      for(k = -r; k <= r; k++)
		{
		  pixelInt p = *(copy+i+(width*(l+k+r)));
		  red = p.red;
		  green = p.green;
		  blue = p.blue;

		  // double p = copy.getf(l+k+r,j);
		  rsum += red * kernel.kernel_double[k+r];
		  gsum += green * kernel.kernel_double[k+r];
		  bsum += blue * kernel.kernel_double[k+r];
		}
	      pixelInt p;

	      // round floats
	      p.red = (int)rsum;
	      p.green = (int)gsum;
	      p.blue = (int)bsum;

	      *(image+(width*(j+r)+i)) = p;
	    }
	}
    }

  // the integer version; this contains a lot of tricky pointer arithmetic
  // need to clean it up and look for ways to speed up computation
  else
    {
      int rsum, gsum, bsum, red, green, blue;
      int length = width * height;

      for(i = 0; i < width; i++)
	{
	  for(j = -r; j < height-r; j++)
	    {
	      int l = ((j + w) % w);
	      rsum = 0.0;
	      gsum = 0.0;
	      bsum = 0.0;
	      for(k = -r; k <= r; k++)
		{
		  pixelInt p = *(copy+i+(width*(l+k+r)));
		  red = p.red;
		  green = p.green;
		  blue = p.blue;

		  // double p = copy.getf(l+k+r,j);
		  rsum += red * kernel.kernel_int[k+r];
		  gsum += green * kernel.kernel_int[k+r];
		  bsum += blue * kernel.kernel_int[k+r];
		}

	      // store results to intermediate array
	      int offset = width*(j+r)+(i);
	      image[offset].red = rsum;
	      image[offset].green = gsum;
	      image[offset].blue = bsum;
	    }
	}

      // normalize results if kernel sum != 0
      if(kernel.sum != 0)
	{
	  for(i = 0; i < length; i++)
	    {
	      // normalize values
	      image[i].red = ((float)image[i].red)/kernel.sum;
	      image[i].green = ((float)image[i].green)/kernel.sum;
	      image[i].blue = ((float)image[i].blue)/kernel.sum;
	    }
	}
    }
  free(copy);
}

int* gray_convolve_in_X(int* image, kernel_1d kernel, int width, int height)
{
	int length = width * height;
	int* copy = malloc(length * sizeof(int));
	memcpy(copy, image, length*sizeof(int));

	// convolve in X
	int r = kernel.length/2;
	int w = width - 2 * r;
	int i, j, k;

	// use int convolution for faster results but some slight data loss
	int sum = 0;

	for(j = 0; j < height; j++)
	{
		for(i = -r; i < width-r; i++)
		{
			int l = ((i + w) % w);
			sum = 0;
			for(k = -r; k <= r; k++)
			{
				int val = *(copy+(j*width)+l+k+r);
				sum += val * kernel.kernel_int[k+r];
			}

			// store the results to intermediate array
			int offset = (j*width+i+r);
			image[offset] = sum;
		}
	}

	// normalize results if kernel sum != 0
	if(kernel.sum != 0)
	{
		for(i = 0; i < length; i++)
		{
			// normalize values
			image[i] = ((float)image[i])/kernel.sum;
		}
	}

	free(copy);
}

int* gray_convolve_in_Y(int* image, kernel_1d kernel, int width, int height)
{
	int length = width * height;
	int* copy = malloc(length * sizeof(int));
	memcpy(copy, image, length*sizeof(int));

	// convolve in X
	int r = kernel.length/2;
	int w = height - 2 * r;
	int i, j, k;

	// use int convolution for faster results but some slight data loss
	int sum = 0;

	for(i = 0; i < width; i++)
	{
		for(j = -r; j < height-r; j++)
		{
			int l = ((j + w) % w);
			sum = 0;
			for(k = -r; k <= r; k++)
			{
				int val = *(copy+i+(width*(l+k+r)));
				sum += val * kernel.kernel_int[k+r];
			}

			// store the results to intermediate array
			int offset = width*(j+r)+(i);
			image[offset] = sum;
		}
	}

	// normalize results if kernel sum != 0
	if(kernel.sum != 0)
	{
		for(i = 0; i < length; i++)
		{
			// normalize values
			image[i] = ((float)image[i])/kernel.sum;
		}
	}

	free(copy);
}
