// Nathan Wingert - u0687928
// Image Processing Library Test Source
// Converting to pixels, testing

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "ImProc_pixels.h"

#define MIN3(x,y,z)  ((y) <= (z) ? \
                         ((x) <= (y) ? (x) : (y)) \
                     : \
                         ((x) <= (z) ? (x) : (z)))

#define MAX3(x,y,z)  ((y) >= (z) ? \
                         ((x) >= (y) ? (x) : (y)) \
                     : \
                         ((x) >= (z) ? (x) : (z)))

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
      image[i] = (newGray > 255) ? 255 : newGray;
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


unsigned char* Threshold_Gray(unsigned char* image, int alpha, int width, int height)
{
  int i = 0;
  int length = width * height;

  for(i; i < length; i++)
    {
      // compute new pixel data
      unsigned char newPixel = image[i];
      
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

pixel* Invert_Pixels_D(pixel* image, int width, int height)
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

pixel* Modify_Brightness_D(pixel* image, int alpha, int width, int height)
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

      image[i] = p;
    }
  return image;
}

pixel* Modify_Contrast_D(pixel* image, int alpha, int width, int height)
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

      image[i] = p;
    }
  return image;
}

pixel* Threshold_D(pixel* image, int alpha, int width, int height)
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

pixel* Gamma_Corr_D(pixel* image, double alpha,  int width, int height)
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

pixel* Modify_Alpha_D(pixel* image, int alpha, int width, int height)
{
  int i = 0;
  int length = width * height;

  for(i; i < length; i++)
    {
      image[i].alpha += alpha;
    }
  return image;
}

pixel* Modify_Contrast_ND(pixel* image, int alpha, int width, int height, pixel* output)
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

pixel* Modify_Brightness_ND(pixel* image, int alpha, int width, int height, pixel* output)
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

pixel* Threshold_ND(pixel* image, int alpha, int width, int height, pixel* output)
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

pixel* Gamma_Corr_ND(pixel* image, double alpha, int width, int height, pixel* output)
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

pixel* Modify_Alpha_ND(pixel* image, int alpha, int width, int height, pixel* output)
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

/*
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
  unsigned long** histogram = malloc(3*sizeof(long*));
  for(i = 0; i < 3; i++)
    {
      histogram[i] = (long*)malloc(256*sizeof(long));
    }

  // initialize histogram
  for(i = 0; i < 256; i++)
    {
      histogram[0][i] = 0;
      histogram[1][i] = 0;
      histogram[2][i] = 0;
    }
  Histogram_RGB(image, width, height, histogram);
 
  // get low r value
  i = 0;
  while(r_low == 0){
    if(histogram[0][i] != 0) r_low = i;
    i++;
  }

  // get high r value
  i = 0;
  while(r_high == 0){
    if(histogram[0][255-i] != 0) r_high = 255-i;
    i++;
  }

// get low g value
  i = 0;
  while(g_low == 0){
    if(histogram[1][i] != 0) g_low = i;
    i++;
  }

  // get high g value
  i = 0;
  while(g_high == 0){
    if(histogram[1][255-i] != 0) g_high = 255-i;
    i++;
  }

// get low b value
  i = 0;
  while(b_low == 0){
    if(histogram[2][i] != 0) b_low = i;
    i++;
  }

  // get high b value
  i = 0;
  while(b_high == 0){
    if(histogram[2][255-i] != 0) b_high = 255-i;
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

  Cum_Histogram_RGB(image, width, height, histogram);

  for(i = 0; i < length; i++)
    {
      pixel* oldPixel = &image[i];
    
      oldPixel->red = round(histogram[0][oldPixel->red] * (255.0/length));
      oldPixel->green = round(histogram[1][oldPixel->green] * (255.0/length));
      oldPixel->blue = round(histogram[2][oldPixel->blue] * (255.0/length));
    }
  for(i = 0; i < length; i++)
    {
      pixel* oldPixel = &image[i];
      unsigned long test = histogram[0][i];
	oldPixel->red = 0;
      
    }

  free(histogram);
  return image;
}

*/

// analysis
unsigned long* Histogram_Lum(pixel* image, int width, int height, unsigned long* histogram)
{
  int i = 0;
  int length = width * height;
 
  // convert to grayscale
  unsigned char* lum = malloc(length*sizeof(char));
  RGB_to_Gray_CharArray(image, width, height, lum);

  for(i; i < length; i++)
    {
      unsigned char newGray = lum[i];
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
  unsigned char* lum = malloc(length*sizeof(char));
  RGB_to_Gray_CharArray(image, width, height, lum);

  for(i; i < length; i++)
    {
      pixel p = image[i];
      unsigned char gray = lum[i];

      // get pixel values
      unsigned char red = p.red;
      unsigned char green = p.green;
      unsigned char blue = p.blue;

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
  length = width * height;
  for(i; i < length; i++)
    {
      pixel oldPixel = image[i];
      unsigned char newGray = 0;
      newGray = (oldPixel.red*0.30) + (oldPixel.green*0.59) + (oldPixel.blue*0.11);
      oldPixel.red = newGray;
      oldPixel.green = newGray;
      oldPixel.blue = newGray;
      image[i] = oldPixel;
    }
  return image;
}

// RGB-HSV conversion routines
hsv_pixel* image_rgb_to_hsv(pixel* rgb_image, int width, int height, hsv_pixel* hsv_image)
{
  int i = 0;
  int length = width * height;

  for(i; i < length; i++)
    {
      hsv_image[i] = pixel_rgb_to_hsv(&rgb_image[i]);
    }
  return hsv_image;
}

hsv_pixel pixel_rgb_to_hsv(pixel* rgb)
{
  hsv_pixel hsv;
  hsv.hue = 0;
  hsv.sat = 0;
  hsv.val = 0;
  
  unsigned char r,g,b;
  r = rgb->red;
  g = rgb->green;
  b = rgb->blue;

  double cMax = 255.0;
  unsigned char cHi = MAX3(r, g, b);
  unsigned char cLo = MIN3(r, g, b);
  unsigned char cRng = cHi - cLo;

  hsv.val = cHi/cMax;
  
  if(cHi > 0)
    hsv.sat = (double)cRng/cHi;

  if(cRng > 0)
    {
      double rr = (double)(cHi - r) / cRng;
      double gg = (double)(cHi - g) / cRng;
      double bb = (double)(cHi - b) / cRng;
      double hh;
      if (r == cHi)                      // r is highest color value
	hh = bb - gg;
      else if (g == cHi)                 // g is highest color value
	hh = rr - bb + 2.0;
      else                               // b is highest color value
	hh = gg - rr + 4.0;
      if (hh < 0)
	hh= hh + 6;
      hsv.hue = hh / 6;
    }
	 
  return hsv;
}

pixel* image_hsv_to_rgb(hsv_pixel* hsv_image, int width, int height, pixel* rgb_image)
{
  int i = 0;
  int length = width * height;

  for(i; i < length; i++)
    {
      rgb_image[i] = pixel_hsv_to_rgb(&hsv_image[i]);
    }
  return rgb_image;
}

pixel pixel_hsv_to_rgb(hsv_pixel* hsv)
{
  pixel rgb;
  // h,s,v in [0,1]
  double h, s, v;
  h = hsv->hue;
  s = hsv->sat;
  v = hsv->val;

  float rr = 0, gg = 0, bb = 0;
  float hh = fmod((6 * h),6);                 
  unsigned char c1 = (unsigned char) hh;                     
  float c2 = hh - c1;
  float x = (1 - s) * v;
  float y = (1 - (s * c2)) * v;
  float z = (1 - (s * (1 - c2))) * v;	
  switch (c1) {
  case 0: rr=v; gg=z; bb=x; break;
  case 1: rr=y; gg=v; bb=x; break;
  case 2: rr=x; gg=v; bb=z; break;
  case 3: rr=x; gg=y; bb=v; break;
  case 4: rr=z; gg=x; bb=v; break;
  case 5: rr=v; gg=x; bb=y; break;
  }

  short N = 256;
  rgb.red = (round(rr*N) < N-1) ? round(rr*N) : N-1;
  rgb.green = (round(gg*N) < N-1) ? round(gg*N) : N-1; 
  rgb.blue = (round(bb*N) < N-1) ? round(bb*N) : N-1; 
  
  return rgb;
}

