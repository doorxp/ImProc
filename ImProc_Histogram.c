// ImProc_Histogram.c
// Image Processing Library
// Naming Semantics - All methods called from outside the library have leading capital letters
//                    All utility methods called from within the library have leading lowercase letters
//                    Utility methods should generally not be called from outside the library unless the
//                    implementer understands the function usage and memory allocations involved

#include <math.h>
#include <stdlib.h>
#include "ImProc_Histogram.h"

// automatic contrast "enhancement" methods
// !! these methods are not properly defined for color images
// for grayscale images, simply set one gray value for each pixel
// no separate grayscale methods since these methods are not "real-time" and so
// efficiency is not a major concern

pixel* Histogram_Eq_Gray(pixel* image, int width, int height, pixel* output)
{
  int i;
  int length = width * height;
 
  // allocate memory for "2d" histogram
  unsigned long** histogram = malloc(3*sizeof(long*));
  for(i = 0; i < 3; i++)
    {
      histogram[i] = malloc(256*sizeof(long));
    }

  // initialize histogram
  for(i = 0; i < 256; i++)
    {
      histogram[0][i] = 0;
      histogram[1][i] = 0;
      histogram[2][i] = 0;
    }

  Cum_Histogram_Color(image, width, height, histogram);

  for(i = 0; i < length; i++)
    {
      pixel oldPixel = image[i];
    
      oldPixel.red = round(histogram[0][oldPixel.red] * (255.0/length));
      oldPixel.green = round(histogram[1][oldPixel.green] * (255.0/length));
      oldPixel.blue = round(histogram[2][oldPixel.blue] * (255.0/length));

      output[i] = oldPixel;
    }
/*
  for(i = 0; i < length; i++)
    {
      pixel* oldPixel = &image[i];
      unsigned long test = histogram[0][i];
      oldPixel->red = 0;
      
    }
*/
  free(histogram);
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

  for(i = 1; i < length; i++)
    {
      histogram[i] = histogram[i-1];
    }

  return histogram;
}

unsigned long** Cum_Histogram_Color(pixel* image, int width, int height, unsigned long** histogram)
{
  int i;
  int length = width * height;

  Histogram_Color(image, width, height, histogram);

  for(i = 1; i < 255; i++)
    {
      histogram[0][i] = histogram[0][i-1] + histogram[0][i];
      histogram[1][i] = histogram[1][i-1] + histogram[1][i];
      histogram[2][i] = histogram[2][i-1] + histogram[2][i];
      histogram[3][i] = histogram[3][i-1] + histogram[3][i];
    }

  return histogram;
}
