// Nathan Wingert - u0687928
// Image Processing Library Test Source

#include <stdio.h>
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
      image[i] = (newPixel > alpha) ? 255 : 0;
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

