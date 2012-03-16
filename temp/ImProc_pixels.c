// Nathan Wingert - u0687928
// Image Processing Library Test Source
// Converting to pixels, testing

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "ImProc.h"

// grayscale point operations
unsigned char* Invert_Pixels_Gray(unsigned char* image, int width, int height)
{
  int i = 0;      
  int length = width * height;

  for(i; i < length; i++)
    {
      image[i] = 255 - image[i];
    }
  return image;
}

unsigned char* Modify_Brightness_Gray(unsigned char* image, int alpha, int width, int height)
{
  int i = 0;
  int length = width * height;

  for(i; i < length; i++)
    {
      // compute new pixel data
      unsigned char newGray = image[i] + alpha;
      
      // clamp pixel data to 0/255 (assuming 8 bit depth)
      image[i] = (newPixel > 255) ? 255 : newGray;
    }
  return image;
}

unsigned char* Modify_Contrast_Gray(unsigned char* image, int alpha, int width, int height)
{
  int i = 0;
  int length = width * height;

  for(i; i < length; i++)
    {
      // compute new pixel data
      unsigned char newGray = image[i] * alpha;
      
      // clamp pixel data to 0/255 (assuming 8 bit depth)
      image[i] = (newGray > 255) ? 255 : newGray;
    }
  return image;
}

unsigned char* Modify_Brightness_Gray(unsigned char* image, int alpha, int width, int height)
{
  int i = 0;
  int length = width * height;

  for(i; i < length; i++)
    {
      // compute new pixel data
      unsigned char newGray = image[i] + alpha;
      
      // clamp pixel data to 0/255 (assuming 8 bit depth)
      image[i] = (newPixel > 255) ? 255 : newGray;
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

unsigned char* Gamma_Corr_Gray(unsigned char* image, double alpha,  int width, int height)
{
  int i, a;
  i = a = 0;
  int length = width * height;

  int K = 256;
  int aMax = K - 1;
  double GAMMA = alpha;
  
  unsigned char lookupTable[K];

  // compute lookup table
  for(a = 0; a < K; a++)
    {
      double aa = (double) a / aMax;
      double bb = pow(aa, GAMMA);

      unsigned char b = (unsigned char) round(bb * aMax);
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

pixel* Invert_Pixels(pixel* image, int width, int height)
{
  int i = 0;      
  int length = width * height;

  for(i; i < length; i++)
    {
      pixel p = image[i];
      p.red = 255 - p.red;
      p.green = 255 - p.green;
      p.blue = 255 - p.blue;
      image[i] = p;
    }
  return image;
}

pixel* Modify_Brightness(pixel* image, int alpha, int width, int height)
{
  int i = 0;
  int length = width * height;

  for(i; i < length; i++)
    {
      // compute new pixel data
      pixel p = image[i];
      p.red = p.red * alpha;
      p.green = p.green * alpha;
      p.blue = p.blue * alpha;
      
      // clamp pixel data to 0/255 (assuming 8 bit depth)
      p.red = p.red + alpha;
      p.green = p.green + alpha;
      p.blue = p.blue + alpha;
      
      // clamp pixel data to 0/255 (assuming 8 bit depth)
      p.red = (p.red > 255) ? 255 : p.red;
      p.green = (p.green > 255) ? 255 : p.green;
      p.blue = (p.blue > 255) ? 255 : p.blue;

      image[i] = p;
    }
  return image;
}

pixel* Modify_Contrast(pixel* image, int alpha, int width, int height)
{
  int i = 0;
  int length = width * height;

  for(i; i < length; i++)
    {
      // compute new pixel data
      pixel p = image[i];
      p.red = p.red * alpha;
      p.green = p.green * alpha;
      p.blue = p.blue * alpha;
      
      // clamp pixel data to 0/255 (assuming 8 bit depth)
      p.red = p.red * alpha;
      p.green = p.green * alpha;
      p.blue = p.blue * alpha;
      
      // clamp pixel data to 0/255 (assuming 8 bit depth)
      p.red = (p.red > 255) ? 255 : p.red;
      p.green = (p.green > 255) ? 255 : p.green;
      p.blue = (p.blue > 255) ? 255 : p.blue;

      image[i] = p;
    }
  return image;
}

pixel* Threshold(pixel* image, int alpha, int width, int height)
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
      image[i] = p;
    }
  return image;
}

pixel* Gamma_Corr(pixel* image, double alpha,  int width, int height)
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
      image[i] = p;
    }
  return image;
}

// automatic contrast "enhancement" methods
// !! these methods are not properly defined for color images
// for grayscale images, simply set one gray value for each pixel
// no separate grayscale methods since these methods are not "real-time" and so
// efficiency is not a major concern

pixel* Auto_Contrast(pixel* image, int width, int height)
{
  int i;
  unsigned char r_low, r_high, g_low, g_high, b_low, b_high;
  i = r_low = r_high = g_low = g_high = b_low = b_high = 0;
  int length = width * height;

  // allocate memory for "2d" histogram
  unsigned long** histogram = (long**)malloc(3*sizeof(long*));
  for(i = 0; i < 3; i++)
    {
      histogram+i = (long*)malloc(256*sizeof(long));
    }

  // initialize histogram
  for(i = 0; i < 256; i++)
    {
      histogram[0][i] = 0;
      histogram[1][i] = 0;
      histogram[2][i] = 0;
    }
  Histogram(image, width, height, histogram);
 
  // get low r value
  i = 0;
  while(r_low == 0){
    if(histogram[i] != 0) r_low = i;
    i++;
  }

  // get high r value
  i = 0;
  while(r_high == 0){
    if(histogram[255-i] != 0) r_high = 255-i;
    i++;
  }

// get low g value
  i = 0;
  while(g_low == 0){
    if(histogram[i] != 0) g_low = i;
    i++;
  }

  // get high g value
  i = 0;
  while(g_high == 0){
    if(histogram[255-i] != 0) g_high = 255-i;
    i++;
  }

// get low b value
  i = 0;
  while(b_low == 0){
    if(histogram[i] != 0) b_low = i;
    i++;
  }

  // get high b value
  i = 0;
  while(b_high == 0){
    if(histogram[255-i] != 0) b_high = 255-i;
    i++;
  }

  for(i = 0; i < length; i++)
    {
      // compute new pixel data
      pixel newPixel;
      pixel oldPixel = image[i];

      // red values
      newPixel.red = oldPixel.red - r_low;
      newPixel.red = newPixel.red * (255.0/(r_high-r_low));

      // green values
     newPixel.green = oldPixel.green - g_low;
     newPixel.green = newPixel.green * (255.0/(g_high-g_low));

      // blue values
     newPixel.blue = oldPixel.blue - b_low;
     newPixel.blue = newPixel.blue * (255.0/(b_high-b_low));

     image[i] = newPixel;
    }

  free(histogram);
  return image;
}

pixel* Histogram_Eq(pixel* image, int width, int height)
{
  int i;
  int length = width * height;
 
  // allocate memory for "2d" histogram
  unsigned long** histogram = (long**)malloc(3*sizeof(long*));
  for(i = 0; i < 3; i++)
    {
      histogram+i = (long*)malloc(256*sizeof(long));
    }

  // initialize histogram
  for(i = 0; i < 256; i++)
    {
      histogram[0][i] = 0;
      histogram[1][i] = 0;
      histogram[2][i] = 0;
    }

  Cum_Histogram(image, width, height, histogram);

  for(i = 0; i < length; i++)
    {
      pixel* oldPixel = &image[i];
      oldPixel->red = round(histogram[0][oldPixel->red] * (255.0/length));
      oldPixel->green = round(histogram[1][oldPixel->green] * (255.0/length));
      oldPixel->blue = round(histogram[2][oldPixel ->blue] * (255.0/length));
    }

  return image;
}


// analysis
// use Histogram_Gray for grayscale images (unsigned char arrays)
unsigned long* Histogram_Gray(unsigned char* image, int width, int height, unsigned long* histogram)
{
  int i = 0;
  int length = width * height;
 
  for(i; i < length; i++)
    {
      unsigned char* newGray = image[i];
      histogram[newGray] = histogram[newGray] + 1;
    }
  return histogram;
}

// use Histogram_RGB for pixel arrays
// !! this histogram type is not valid for RGB
// only here for testing
unsigned long** Histogram_RGB(pixel* image, int width, int height, unsigned long** histogram)
{
  int i = 0;
  int length = width * height;

  for(i; i < length; i++)
    {
      pixel p = image[i];

      // get pixel values
      int red = p.red;
      int green = p.green;
      int blue = p.blue;

      histogram[0][red] = histogram[0][red] + 1;
      histogram[1][green] = histogram[1][green] + 1;
      histogram[2][blue] = histogram[2][blue] + 1;
    }
  return histogram;
}

// use this method to return a grayscale histogram for the input RGB pixel array
unsigned long* Histogram_RGB_toGray(pixel* image, int width, int height, unsigned long* histogram)
{
  int i = 0;
  int length = width * height;
 
  // setup up grayscale array
  unsigned char* grayArray = (unsigned char*)malloc(length*sizeof(char));
  for(i; i < length; i++)
    grayArray[i] = 0;

  // compute grayscale histogram
  RGB_to_Gray_CharArray(image, width, height, grayArray);
  Histogram_Gray(grayArray, width, height, histogram);
  
  // free memory and return
  free(grayArray);
  return histogram;
}

// cumulative histograms should follow the same usage procedures as regular histograms
unsigned long* Cum_Histogram_Gray(unsigned char* image, int width, int height, unsigned long* histogram)
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
      image[i] = newPixel;
    }

  free(histogram);
  return image;

unsigned long** Cum_Histogram(struct pixel* image, int width, int height, unsigned long** histogram)
{
  int i;
  int length = width * height;

  Histogram(image, width, height, histogram);

  for(i = 1; i < 255; i++)
    {
      histogram[0][i] = histogram[0][i-1] + histogram[0][i];
      histogram[1][i] = histogram[1][i-1] + histogram[1][i];
      histogram[2][i] = histogram[2][i-1] + histogram[2][i];
    }

  return histogram;
}

// utility methods


// utility methods
// RGB to grayscale conversion 1:
// Original pixel array is not modified; grayscale array is updated with correct grayscale values
// Use this if you want a smaller grayscale image representation
unsigned char* RGB_to_Gray_CharArray(pixel* image, int width, int height, unsigned char* gray_Image)
{
  int i, length;
  i = length = 0;
  for(i; i < length; i++)
    {
      pixel oldPixel = image[i];
      unsigned char newGray = 0;
      newGray = (oldPixel.red*0.30) + (oldPixel.green*0.59) + (oldPixel.blue*0.11);
      gray_Image[i] = newGray;
    }
}

// RGB to grayscale conversion 2:
// Original pixel array is modified with grayscale values for each pixel
// Use this if you want to convert to grayscale but maintain the original image data structure
pixel* RGB_to_Gray_PixelArray(pixel* image, int width, int height)
{
  int i, length;
  i = length = 0;
  for(i; i < length; i++)
    {
      pixel* oldPixel = &image[i];
      unsigned char newGray = 0;
      newGray = (oldPixel->red*0.30) + (oldPixel->green*0.59) + (oldPixel->blue*0.11);
      oldPixel->red = newGray;
      oldPixel->green = newGray;
      oldPixel->blue = newGray;
    }
}
