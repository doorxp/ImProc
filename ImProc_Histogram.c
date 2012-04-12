// ImProc_Histogram.c
// Image Processing Library
// Naming Semantics - All methods called from outside the library have leading capital letters
//                    All utility methods called from within the library have leading lowercase letters
//                    Utility methods should generally not be called from outside the library unless the
//                    implementer understands the function usage and memory allocations involved

#include <math.h>
#include <stdlib.h>
#include "ImProc_Histogram.h"
#include "ImProc_Utils.h"

// automatic contrast "enhancement" methods
// !! these methods are not properly defined for color images
// for grayscale images, simply set one gray value for each pixel
// no separate grayscale methods since these methods are not "real-time" and so
// efficiency is not a major concern

pixel* Histogram_Eq_Gray(pixel* image, int width, int height, pixel* output)
{
  int i;
  int length = width * height;
 
  // convert to grayscale
  RGB_to_Gray_PixelArray(image, width, height, output);

  // allocate/initialize memory for grayscale histogram
  unsigned long* histogram = malloc(256*sizeof(long));
  for(i = 0; i < 256; i++)
      histogram[i] = 0;

  Cum_Histogram_Lum(output, width, height, histogram);

  for(i = 0; i < length; i++)
    {
      pixel oldPixel = output[i];

      // any val would work here since they are all the same for gray
      int val = oldPixel.red;
      int newVal = round(histogram[val] * (255.0/length));
    
      oldPixel.red = newVal;
      oldPixel.green = newVal;
      oldPixel.blue = newVal;

      output[i] = oldPixel;
    }

  free(histogram);
  return output;
}

// convert image to hsv color space and run histogram equilization on intensity values
pixel* Histogram_Eq_Color(pixel* image, int width, int height, pixel* output)
{
	int i;
	int length = width * height;
	
	// convert image to hsv color sapce
	hsv_pixel* hsv_image = malloc(length*sizeof(hsv_pixel));
	Image_RGB_to_HSV(image, width, height, hsv_image);

	// initialize vals array and histogram
	pixel* hsv_vals = malloc(length*sizeof(pixel));

	// compute vals array
	for(i = 0; i < length; i++)
	{
		pixel newPixel;
		newPixel.red = newPixel.green = newPixel.blue = round(hsv_image[i].val*255.0);
	    hsv_vals[i] = newPixel;
	}
	// build rgb image from hsv vals
		
	// run histogram equilization on hsv vals
	Histogram_Eq_Gray(hsv_vals, width, height, hsv_vals);
	
	// copy hsv vals back to original image
	for(i = 0; i < length; i++)
	  hsv_image[i].val = hsv_vals[i].red/255.0;
		
	// convert equalized hsv image back to rgb 
	Image_HSV_to_RGB(hsv_image, width, height, output);
	
	free(hsv_image);
	free(hsv_vals);
	return output;
}


// analysis 
unsigned long* Histogram_Lum(pixel* image, int width, int height, unsigned long* histogram)
{
  int i = 0;
  int length = width * height;
 
  // convert to grayscale
  int* lum = malloc(length*sizeof(int));
  RGB_to_Gray_IntArray(image, width, height, lum);

  for(i; i < length; i++)
    {
      int newGray = lum[i];
      histogram[newGray] = histogram[newGray] + 1;
    }

  free(lum);
  return histogram;
}

// color histogram with individual color information and luminosity
unsigned long** Histogram_Color(pixel* image, int width, int height, unsigned long** histogram)
{
  int i = 0;
  int length = width * height;

  // convert to grayscale for intensity values
  int* lum = malloc(length*sizeof(int));
  RGB_to_Gray_IntArray(image, width, height, lum);

  for(i; i < length; i++)
    {
      pixel p = image[i];
      unsigned char gray = lum[i];

      // get pixel values
      int red = p.red;
      int green = p.green;
      int blue = p.blue;

      histogram[0][gray] = histogram[0][gray] + 1;
      histogram[1][red] = histogram[1][red] + 1;
      histogram[2][green] = histogram[2][green] + 1;
      histogram[3][blue] = histogram[3][blue] + 1;
    }

  free(lum);
  return histogram;
}

// cumulative histograms should follow the same usage procedures as regular histograms
unsigned long* Cum_Histogram_Lum(pixel* image, int width, int height, unsigned long* histogram)
{
  int i = 0;
  int length = width * height;
 
  Histogram_Lum(image, width, height, histogram);

  for(i = 1; i < 256; i++)
    {
      histogram[i] = histogram[i-1] + histogram[i];
    }

  return histogram;
}

unsigned long** Cum_Histogram_Color(pixel* image, int width, int height, unsigned long** histogram)
{
  int i;
  int length = width * height;

  Histogram_Color(image, width, height, histogram);

  for(i = 1; i < 256; i++)
    {
      histogram[0][i] = histogram[0][i-1] + histogram[0][i];
      histogram[1][i] = histogram[1][i-1] + histogram[1][i];
      histogram[2][i] = histogram[2][i-1] + histogram[2][i];
      histogram[3][i] = histogram[3][i-1] + histogram[3][i];
    }

  return histogram;
}

