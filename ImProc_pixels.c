// Nathan Wingert - u0687928
// Image Processing Library Test Source
// Converting to pixels, testing

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "ImProc_pixels.h"

#define MIN3(x,y,z)  ((y) <= (z) ?		\
		      ((x) <= (y) ? (x) : (y))	\
		      :				\
		      ((x) <= (z) ? (x) : (z)))

#define MAX3(x,y,z)  ((y) >= (z) ?		\
		      ((x) >= (y) ? (x) : (y))	\
		      :				\
		      ((x) >= (z) ? (x) : (z)))

#define FLOAT	0
#define INT 	1
#define PIXEL	3
#define ADD     0
#define SUB	1
#define MUL	2
#define DIV	3
#define SQR     4
#define SQRT    5


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
hsv_pixel* Image_RGB_to_HSV(pixel* rgb_image, int width, int height, hsv_pixel* hsv_image)
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

pixel* Image_HSV_to_RGB(hsv_pixel* hsv_image, int width, int height, pixel* rgb_image)
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

pixel* pixel_copy(pixel* image, int width, int height)
{
  int i = 0;
  int length = width * height;
  pixel* copy = malloc(length*sizeof(pixel));

  for(i; i < length; i++)
    {
      pixel p = image[i];
      copy[i] = p;
    }
  return copy;
}

pixelInt* pixelInt_copy(pixelInt* image, int width, int height)
{
  int i = 0;
  int length = width * height;
  pixelInt* copy = malloc(length*sizeof(pixelInt));

  for(i; i < length; i++)
    {
      copy[i] = image[i];
    }
  return copy;
}

// routine for combining two images
pixel* pixel_combine(pixel* image1, pixel* image2, int width, int height, int ctype)
{
  int i = 0;
  int length = width * height;
  int tempRed, tempGreen, tempBlue;

  // addition
  if(ctype == ADD)
    {
      for(i; i < length; i++)
	{
	  tempRed = image1[i].red + image2[i].red;
	  tempGreen = image1[i].green + image2[i].green;
	  tempBlue = image1[i].blue + image2[i].blue;

	  // clamp values
	  tempRed = tempRed > 255 ? 255 : tempRed < 0 ? 0 : tempRed;
	  tempGreen = tempGreen > 255 ? 255 : tempGreen < 0 ? 0 : tempGreen;
	  tempBlue = tempBlue > 255 ? 255 : tempBlue < 0 ? 0 : tempBlue;

	  image1[i].red = (unsigned char)tempRed;
	  image1[i].green = (unsigned char)tempGreen;
	  image1[i].blue = (unsigned char)tempBlue;
	}
    }

  // subtraction
  else if(ctype == SUB)
    {
      for(i; i < length; i++)
	{
	  tempRed = image1[i].red - image2[i].red;
	  tempGreen = image1[i].green - image2[i].green;
	  tempBlue = image1[i].blue - image2[i].blue;

	  // clamp values
	  tempRed = tempRed > 255 ? 255 : tempRed < 0 ? 0 : tempRed;
	  tempGreen = tempGreen > 255 ? 255 : tempGreen < 0 ? 0 : tempGreen;
	  tempBlue = tempBlue > 255 ? 255 : tempBlue < 0 ? 0 : tempBlue;

	  image1[i].red = (unsigned char)tempRed;
	  image1[i].green = (unsigned char)tempGreen;
	  image1[i].blue = (unsigned char)tempBlue;
	}
    }

  // TODO - add multiplication and division
  return image1;
}

pixel* pixel_pointOp(pixel* image, float alpha, int width, int height, int ctype)
{
  int i = 0;
  int length = width * height;
  int tempRed, tempGreen, tempBlue;
  int intAlpha = (int)alpha;

  // if alpha corresponds to an integer value then do int ops to save time
  if(ceilf(alpha) == alpha)
    {
      if(ctype == ADD)
	{
	  for(i; i < length; i++)
	    {
	      tempRed = image[i].red + intAlpha;
	      tempGreen = image[i].green + intAlpha;
	      tempBlue = image[i].blue + intAlpha;

	      // clamp values
	      tempRed = tempRed > 255 ? 255 : tempRed < 0 ? 0 : tempRed;
	      tempGreen = tempGreen > 255 ? 255 : tempGreen < 0 ? 0 : tempGreen;
	      tempBlue = tempBlue > 255 ? 255 : tempBlue < 0 ? 0 : tempBlue;

	      image[i].red = (unsigned char)tempRed;
	      image[i].green = (unsigned char)tempGreen;
	      image[i].blue = (unsigned char)tempBlue;
	    }
	}

      else if(ctype == SUB)
	{
	  for(i; i < length; i++)
	    {
	      tempRed = image[i].red - intAlpha;
	      tempGreen = image[i].green - intAlpha;
	      tempBlue = image[i].blue - intAlpha;

	      // clamp values
	      tempRed = tempRed > 255 ? 255 : tempRed < 0 ? 0 : tempRed;
	      tempGreen = tempGreen > 255 ? 255 : tempGreen < 0 ? 0 : tempGreen;
	      tempBlue = tempBlue > 255 ? 255 : tempBlue < 0 ? 0 : tempBlue;

	      image[i].red = (unsigned char)tempRed;
	      image[i].green = (unsigned char)tempGreen;
	      image[i].blue = (unsigned char)tempBlue;
	    }
	}

      else if(ctype == MUL)
	{
	  for(i; i < length; i++)
	    {
	      tempRed = image[i].red * intAlpha;
	      tempGreen = image[i].green * intAlpha;
	      tempBlue = image[i].blue * intAlpha;

	      // clamp values
	      tempRed = tempRed > 255 ? 255 : tempRed < 0 ? 0 : tempRed;
	      tempGreen = tempGreen > 255 ? 255 : tempGreen < 0 ? 0 : tempGreen;
	      tempBlue = tempBlue > 255 ? 255 : tempBlue < 0 ? 0 : tempBlue;

	      image[i].red = (unsigned char)tempRed;
	      image[i].green = (unsigned char)tempGreen;
	      image[i].blue = (unsigned char)tempBlue;
	    }
	}

      else
	{
	  for(i; i < length; i++)
	    {
	      tempRed = image[i].red / intAlpha;
	      tempGreen = image[i].green / intAlpha;
	      tempBlue = image[i].blue / intAlpha;

	      // clamp values
	      tempRed = tempRed > 255 ? 255 : tempRed < 0 ? 0 : tempRed;
	      tempGreen = tempGreen > 255 ? 255 : tempGreen < 0 ? 0 : tempGreen;
	      tempBlue = tempBlue > 255 ? 255 : tempBlue < 0 ? 0 : tempBlue;

	      image[i].red = (unsigned char)tempRed;
	      image[i].green = (unsigned char)tempGreen;
	      image[i].blue = (unsigned char)tempBlue;
	    }
	}
    }

  else
    {
      if(ctype == ADD)
	{
	  for(i; i < length; i++)
	    {
	      tempRed = image[i].red + alpha;
	      tempGreen = image[i].green + alpha;
	      tempBlue = image[i].blue + alpha;

	      // clamp values
	      tempRed = tempRed > 255 ? 255 : tempRed < 0 ? 0 : tempRed;
	      tempGreen = tempGreen > 255 ? 255 : tempGreen < 0 ? 0 : tempGreen;
	      tempBlue = tempBlue > 255 ? 255 : tempBlue < 0 ? 0 : tempBlue;

	      image[i].red = (unsigned char)tempRed;
	      image[i].green = (unsigned char)tempGreen;
	      image[i].blue = (unsigned char)tempBlue;
	    }
	}

      else if(ctype == SUB)
	{
	  for(i; i < length; i++)
	    {
	      tempRed = image[i].red - alpha;
	      tempGreen = image[i].green - alpha;
	      tempBlue = image[i].blue - alpha;

	      // clamp values
	      tempRed = tempRed > 255 ? 255 : tempRed < 0 ? 0 : tempRed;
	      tempGreen = tempGreen > 255 ? 255 : tempGreen < 0 ? 0 : tempGreen;
	      tempBlue = tempBlue > 255 ? 255 : tempBlue < 0 ? 0 : tempBlue;

	      image[i].red = (unsigned char)tempRed;
	      image[i].green = (unsigned char)tempGreen;
	      image[i].blue = (unsigned char)tempBlue;
	    }
	}

      else if(ctype == MUL)
	{
	  for(i; i < length; i++)
	    {
	      tempRed = image[i].red * alpha;
	      tempGreen = image[i].green * alpha;
	      tempBlue = image[i].blue * alpha;

	      // clamp values
	      tempRed = tempRed > 255 ? 255 : tempRed < 0 ? 0 : tempRed;
	      tempGreen = tempGreen > 255 ? 255 : tempGreen < 0 ? 0 : tempGreen;
	      tempBlue = tempBlue > 255 ? 255 : tempBlue < 0 ? 0 : tempBlue;

	      image[i].red = (unsigned char)tempRed;
	      image[i].green = (unsigned char)tempGreen;
	      image[i].blue = (unsigned char)tempBlue;
	    }
	}

      else
	{
	  for(i; i < length; i++)
	    {
	      tempRed = image[i].red / alpha;
	      tempGreen = image[i].green / alpha;
	      tempBlue = image[i].blue / alpha;

	      // clamp values
	      tempRed = tempRed > 255 ? 255 : tempRed < 0 ? 0 : tempRed;
	      tempGreen = tempGreen > 255 ? 255 : tempGreen < 0 ? 0 : tempGreen;
	      tempBlue = tempBlue > 255 ? 255 : tempBlue < 0 ? 0 : tempBlue;

	      image[i].red = (unsigned char)tempRed;
	      image[i].green = (unsigned char)tempGreen;
	      image[i].blue = (unsigned char)tempBlue;
	    }
	}
    }
}

pixelInt* pixel_to_pixelInt(pixel* image, int width, int height, pixelInt* newImage)
{
  int i, j;
  int length = width * height;
  if(newImage == NULL)
    newImage = malloc(length*sizeof(pixelInt));

  for(i = 0; i < length; i++)
    {
      newImage[i].red = image[i].red;
      newImage[i].green = image[i].green;
      newImage[i].blue = image[i].blue;
    }
  return newImage;
}

pixel* pixelInt_to_pixel(pixelInt* image, int width, int height, pixel* newImage)
{
  int i, j;
  int length = width * height;

  if(newImage == NULL)
    newImage = malloc(length*sizeof(pixel));

  for(i = 0; i < length; i++)
    {
      newImage[i].red = image[i].red > 255 ? 255 : image[i].red < 0 ? 0 : image[i].red;
      newImage[i].green = image[i].green > 255 ? 255 : image[i].green < 0 ? 0 : image[i].green;
      newImage[i].blue = image[i].blue > 255 ? 255 : image[i].blue < 0 ? 0 : image[i].blue;
      newImage[i].alpha = 255;
    }
  return newImage;
}

// routine for combining two images
pixelInt* pixelInt_combine(pixelInt* image1, pixelInt* image2, int width, int height, int ctype)
{
  int i = 0;
  int length = width * height;
  int tempRed, tempGreen, tempBlue;

  // addition
  if(ctype == ADD)
    {
      for(i; i < length; i++)
	{
	  image1[i].red += image2[i].red;
	  image1[i].green += image2[i].green;
	  image1[i].blue += image2[i].blue;
	}
    }

  // subtraction
  else if(ctype == SUB)
    {
      for(i; i < length; i++)
	{
	  image1[i].red -= image2[i].red;
	  image1[i].green -= image2[i].green;
	  image1[i].blue -= image2[i].blue;
	}
    }

  // TODO - add multiplication and division
  return image1;
}

pixelInt* pixelInt_pointOp(pixelInt* image, float alpha, int width, int height, int ctype)
{
  int i = 0;
  int length = width * height;
  int intAlpha = (int)alpha;

  // if alpha corresponds to an integer value then do int ops to save time
  if(ceilf(alpha) == alpha)
    {
      if(ctype == ADD)
	{
	  for(i; i < length; i++)
	    {
	      image[i].red += intAlpha;
	      image[i].green += intAlpha;
	      image[i].blue += intAlpha;
	    }
	}

      else if(ctype == SUB)
	{
	  for(i; i < length; i++)
	    {
	      image[i].red -= intAlpha;
	      image[i].green -= intAlpha;
	      image[i].blue -= intAlpha;
	    }
	}

      else if(ctype == MUL)
	{
	  for(i; i < length; i++)
	    {
	      image[i].red *= intAlpha;
	      image[i].green *= intAlpha;
	      image[i].blue *= intAlpha;
	    }
	}
      else if(ctype == SQR)
	{
	  for(i; i < length; i++)
	    {
	      image[i].red = pow(image[i].red, 2);
	      image[i].green = pow(image[i].green, 2);
	      image[i].blue = pow(image[i].blue, 2);
	    }
	}
      else if(ctype == SQRT)
	{
	  for(i; i < length; i++)
	    {
	      image[i].red = sqrt(image[i].red);
	      image[i].green = sqrt(image[i].green);
	      image[i].blue = sqrt(image[i].blue);
	    }
	}
      else
	{
	  for(i; i < length; i++)
	    {
	      image[i].red /= intAlpha;
	      image[i].green /= intAlpha;
	      image[i].blue /= intAlpha;
	    }
	}
    }

  else
    {
       if(ctype == ADD)
	{
	  for(i; i < length; i++)
	    {
	      image[i].red += alpha;
	      image[i].green += alpha;
	      image[i].blue += alpha;
	    }
	}

      else if(ctype == SUB)
	{
	  for(i; i < length; i++)
	    {
	      image[i].red -= alpha;
	      image[i].green -= alpha;
	      image[i].blue -= alpha;
	    }
	}

      else if(ctype == MUL)
	{
	  for(i; i < length; i++)
	    {
	      image[i].red *= alpha;
	      image[i].green *= alpha;
	      image[i].blue *= alpha;
	    }
	}
      else if(ctype == SQR)
	{
	  for(i; i < length; i++)
	    {
	      image[i].red = pow(image[i].red, 2);
	      image[i].green = pow(image[i].green, 2);
	      image[i].blue = pow(image[i].blue, 2);
	    }
	}
      else if(ctype == SQRT)
	{
	  for(i; i < length; i++)
	    {
	      image[i].red = sqrt(image[i].red);
	      image[i].green = sqrt(image[i].green);
	      image[i].blue = sqrt(image[i].blue);
	    }
	}
      else
	{
	  for(i; i < length; i++)
	    {
	      image[i].red /= alpha;
	      image[i].green /= alpha;
	      image[i].blue /= alpha;
	    }
	}
    }
}

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

pixel* Gaussian_Blur(pixel* image, double sigma, int width, int height, int dtype)
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
  pixelInt_to_pixel(cimage, width, height, image);

  // free the kernel pointers and pixelInt image
  free(kernel.kernel_double);
  free(kernel.kernel_int);
  free(cimage);

  return image;
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

pixel* Fast_Blur(pixel* image, int width, int height)
{
  int i = 0;
  int length = width * height;

  // build box filter kernel
  int box_filter[3] = {1, 1, 1};
  kernel_1d box_kernel;
  box_kernel.kernel_int = box_filter;
  box_kernel.length = 3;
  box_kernel.sum = 3;

  // convolve
  pixelInt* cimage = pixel_to_pixelInt(image, width, height, NULL);
  convolve_in_X(cimage, box_kernel, width, height, 1);
  convolve_in_Y(cimage, box_kernel, width, height, 1);
  pixelInt_to_pixel(cimage, width, height, image);

  free(cimage);
  return image;
}

pixel* Fast_Sharpen(pixel* image, int width, int height)
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
   pixelInt_to_pixel(image1, width, height, image);

   free(image1);
   free(image2);

   return image;
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

// edge detection
pixel* Gradient_Magnitude(pixel* image, double sigma, int width, int height)
{
  int i = 0;
  int length = width * height;

  // compute the kernel
  kernel_1d g_kernel = Make_Gaussian_1d_Kernel(sigma);

  // build box filter kernel
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

  pixelInt_to_pixel(image1, width, height, image);
  Threshold_D(image, 5, width, height);
  
  // free memory
  free(image1);
  free(image2);

  return image;
}

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
	      float redf, greenf, bluef;
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
	      float redf, greenf, bluef;
	      image[i].red = ((float)image[i].red)/kernel.sum;
	      image[i].green = ((float)image[i].green)/kernel.sum;
	      image[i].blue = ((float)image[i].blue)/kernel.sum;
	    }
	}
    }
  free(copy);
}
