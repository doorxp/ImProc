// Nathan Wingert - u0687928
// Image Processing Library Test Source

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "ImProc.h"

unsigned short* Invert_Pixels(unsigned short* image, int width, int height)
{
  int i = 0;      
  int length = width * height;

  for(i; i < length; i++)
    {
      image[i] = 255 - image[i];
    }
  return image;
}

unsigned short* Modify_Contrast(unsigned short* image, int alpha, int width, int height)
{
  int i = 0;
  int length = width * height;

  for(i; i < length; i++)
    {
      // compute new pixel data
      short newPixel = image[i] * alpha;
      
      // clamp pixel data to 0/255 (assuming 8 bit depth)
      image[i] = (newPixel > 255) ? 255 : newPixel;
    }
  return image;
}

unsigned short* Modify_Brightness(unsigned short* image, int alpha, int width, int height)
{
  int i = 0;
  int length = width * height;

  for(i; i < length; i++)
    {
      // compute new pixel data
      short newPixel = image[i] + alpha;
      
      // clamp pixel data to 0/255 (assuming 8 bit depth)
      image[i] = (newPixel > 255) ? 255 : newPixel;
    }
  return image;
}

unsigned short* Threshold(unsigned short* image, int alpha, int width, int height)
{
  int i = 0;
  int length = width * height;

  for(i; i < length; i++)
    {
      // compute new pixel data
      short newPixel = image[i];
      
      // clamp pixel data to 0/255 (assuming 8 bit depth)
      image[i] = (newPixel >= alpha) ? 255 : 0;
    }
  return image;
}

unsigned long* Histogram(unsigned short* image, int width, int height, unsigned long* histogram)
{
  int i = 0;
  int length = width * height;
 
  for(i; i < length; i++)
    {
      short newPixel = image[i];
      histogram[newPixel] = histogram[newPixel] + 1;
    }
  return histogram;
}

unsigned long* Cum_Histogram(unsigned short* image, int width, int height, unsigned long* histogram)
{
  int i;
  int length = width * height;
 
  Histogram(image, width, height, histogram);

  for(i = 1; i < 256; i++)
      histogram[i] = histogram[i-1] + histogram[i];

  return histogram;
}

unsigned short* Auto_Contrast(unsigned short* image, int width, int height)
{
  int i;
  short a_low, a_high;
  i = a_low = a_high = 0;
  int length = width * height;

  unsigned long* histogram = malloc(256*sizeof(long));
  for(i = 0; i < 256; i++)
      histogram[i] = 0;
  Histogram(image, width, height, histogram);
 
  // get low value
  i = 0;
  while(a_low == 0){
    if(histogram[i] != 0) a_low = i;
    i++;
  }

  // get high value
  i = 0;
  while(a_high == 0){
    if(histogram[255-i] != 0) a_high = 255-i;
    i++;
  }

  for(i = 0; i < length; i++)
    {
      // compute new pixel data
      short newPixel = image[i] - a_low;
      newPixel = newPixel * (255.0/(a_high-a_low));
    }

  free(histogram);
  return image;
}
