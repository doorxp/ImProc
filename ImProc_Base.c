// ImProc_Base.c
// Nathan Wingert - u0687928
// Image Processing Library
// Naming Semantics - All methods called from outside the library have leading capital letters
//                    All utility methods called from within the library have leading lowercase letters
//                    Utility methods should generally not be called from outside the library unless the
//                    implementer understands the function usage and memory allocations involved

#include <math.h>
#include "ImProc_Base.h"

// grayscale point operations
int* Invert_Pixels_Gray(int* image, int width, int height)
{
  int i = 0;      
  int length = width * height;

  for(i; i < length; i++)
    {
      image[i] = 255 - image[i];
    }
  return image;
}

int* Modify_Brightness_Gray(int* image, int alpha, int width, int height)
{
  int i = 0;
  int length = width * height;

  for(i; i < length; i++)
    {
      // compute new pixel data
      int newGray = image[i] + alpha;
      
      // clamp pixel data to 0/255 (assuming 8 bit depth)
      image[i] = (newGray > 255) ? 255 : newGray;
    }
  return image;
}

int* Modify_Contrast_Gray(int* image, int alpha, int width, int height)
{
  int i = 0;
  int length = width * height;

  for(i; i < length; i++)
    {
      // compute new pixel data
      int newGray = image[i] * alpha;
      
      // clamp pixel data to 0/255 (assuming 8 bit depth)
      image[i] = (newGray > 255) ? 255 : newGray;
    }
  return image;
}


int* Threshold_Gray(int* image, int alpha, int width, int height)
{
  int i = 0;
  int length = width * height;

  for(i; i < length; i++)
    {
      // compute new pixel data
      int newPixel = image[i];
      
      // clamp pixel data to 0/255 (assuming 8 bit depth)
      image[i] = (newPixel >= alpha) ? 255 : 0;
    }
  return image;
}

int* Gamma_Corr_Gray(int* image, double alpha,  int width, int height)
{
  int i, a;
  i = a = 0;
  int length = width * height;

  int K = 256;
  int aMax = K - 1;
  double GAMMA = alpha;
  
  int lookupTable[K];

  // compute lookup table
  for(a = 0; a < K; a++)
    {
      double aa = (double) a / aMax;
      double bb = pow(aa, GAMMA);

      int b = (int) round(bb * aMax);
      lookupTable[a] = b;
    }

  for(i; i < length; i++)
    {
      // apply lookup table to image
      image[i] = lookupTable[image[i]];
    }
  return image;
}

// RGBA point operations
// WARNING: some of these operations are not properly defined for color images

pixel* Invert_Pixels(pixel* image, int width, int height, pixel* output)
{
  int i = 0;      
  int length = width * height;

  for(i; i < length; i++)
    {
      pixel p = image[i];
      p.red = 255 - p.red;
      p.green = 255 - p.green;
      p.blue = 255 - p.blue;
      output[i] = p;
    }
  return output;
}

pixel* Modify_Contrast(pixel* image, int alpha, int width, int height, pixel* output)
{
  int i = 0;
  int length = width * height;
  short tempRed, tempGreen, tempBlue;
  tempRed = tempGreen = tempBlue = 0;

  for(i; i < length; i++)
    {
      
      // compute new pixel data
      pixel p = image[i];

      tempRed = p.red * alpha;
      tempGreen = p.green * alpha;
      tempBlue = p.blue * alpha;

      // clamp pixel data to 0/255 (assuming 8 bit depth)
      if(tempRed > 255)
	tempRed = 255;
      if(tempRed < 0)
	tempRed = 0;
      if(tempGreen > 255)
	tempGreen = 255;
      if(tempGreen < 0)
	tempGreen = 0;
      if(tempBlue > 255)
	tempBlue = 255;
      if(tempBlue < 0)
	tempBlue = 0;

      p.red = (unsigned char)tempRed;
      p.green = (unsigned char)tempGreen;
      p.blue = (unsigned char)tempBlue;

      output[i] = p;
    }
  return output;
}

pixel* Modify_Brightness(pixel* image, int alpha, int width, int height, pixel* output)
{
  int i = 0;
  int length = width * height;
  short tempRed, tempGreen, tempBlue;
  tempRed = tempGreen = tempBlue = 0;

  for(i; i < length; i++)
  {

	  // compute new pixel data
	  pixel p = image[i];

	  tempRed = p.red + alpha;
	  tempGreen = p.green + alpha;
	  tempBlue = p.blue + alpha;

	  // clamp pixel data to 0/255 (assuming 8 bit depth)
	  if(tempRed > 255)
		  tempRed = 255;
	  if(tempRed < 0)
		  tempRed = 0;
	  if(tempGreen > 255)
		  tempGreen = 255;
	  if(tempGreen < 0)
		  tempGreen = 0;
	  if(tempBlue > 255)
		  tempBlue = 255;
	  if(tempBlue < 0)
		  tempBlue = 0;

	  p.red = (unsigned char)tempRed;
	  p.green = (unsigned char)tempGreen;
	  p.blue = (unsigned char)tempBlue;

	  output[i] = p;
  }
  return output;
}

pixel* Threshold(pixel* image, int alpha, int width, int height, pixel* output)
{
  int i = 0;
  int length = width * height;

  for(i; i < length; i++)
    {
      // compute new pixel data
      pixel p = image[i];
      
      // clamp pixel data to 0/255 (assuming 8 bit depth)
      p.red = (p.red > alpha) ? 255 : 0;
      p.green = (p.green > alpha) ? 255 : 0;
      p.blue = (p.blue > alpha) ? 255 : 0;

      // assign new pixel info
      output[i] = p;
    }
  return output;
}

pixel* Gamma_Corr(pixel* image, double alpha, int width, int height, pixel* output)
{
  int i, a;
  i = a = 0;
  int length = width * height;

  int K = 256;
  int aMax = K - 1;
  double GAMMA = alpha;
  
  short lookupTable[K];

  // compute lookup table
  for(a = 0; a < K; a++)
    {
      double aa = (double) a / aMax;
      double bb = pow(aa, GAMMA);

      short b = (short) round(bb * aMax);
      lookupTable[a] = b;
    }

  pixel p;
  for(i; i < length; i++)
    {
      // apply lookup table to image
      p = image[i];
      p.red = lookupTable[p.red];
      p.green = lookupTable[p.green];
      p.blue = lookupTable[p.blue];
      output[i] = p;
    }
  return output;
}

pixel* Modify_Alpha(pixel* image, int alpha, int width, int height, pixel* output)
{
  int i = 0;
  int length = width * height;

  for(i; i < length; i++)
    {
      pixel p = image[i];
      p.alpha += alpha;
      output[i] = p;
    }
  return output;
}
