// ImProc_utils.c
// Image Processing Library
// Naming Semantics - All methods called from outside the library have leading capital letters
//                    All utility methods called from within the library have leading lowercase letters
//                    Utility methods should generally not be called from outside the library unless the
//                    implementer understands the function usage and memory allocations involved

#include <math.h>
#include <stdlib.h>
#include "ImProc_Utils.h"

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

// pixel to pixelInt conversion routines
// utility routines for both formats

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
  return image;
}

// RGB to grayscale conversion 1:
// Original pixel array is not modified; grayscale array is updated with correct grayscale values
int* RGB_to_Gray_IntArray(pixel* image, int width, int height, int* intArray)
{
  int i, length;
  i = length = 0;
  length = width * height;

  if(intArray == NULL)
    intArray = malloc(length*sizeof(int));

  for(i; i < length; i++)
    {
      pixel oldPixel = image[i];
      int newGray = 0;
      newGray = (oldPixel.red*0.30) + (oldPixel.green*0.59) + (oldPixel.blue*0.11);
      intArray[i] = newGray;
    }
  return intArray;
}

// Convert grayscale image back to pixel array
pixel* IntArray_to_PixelArray(int* intArray, int width, int height, pixel* output)
{
  int i, length;
  i = length = 0;
  length = width * height;
  int gray;

  if(output == NULL)
    output = malloc(length*sizeof(pixel));

  for(i = 0; i < length; i++)
    {
      gray = intArray[i] > 255 ? 255 : intArray[i] < 0 ? 0 : intArray[i];
      output[i].red = gray;
      output[i].green = gray;
      output[i].blue = gray;  
      output[i].alpha = 255;
    }

  return output;
}

// RGB to grayscale conversion 2:
// Original pixel array is modified with grayscale values for each pixel
// Use this if you want to convert to grayscale but maintain the original image data structure
pixel* RGB_to_Gray_PixelArray(pixel* image, int width, int height, pixel* output)
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
      output[i] = oldPixel;
    }
  return output;
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

// transforms
pixel* Rotate(pixel* image, int degrees, int width, int height, pixel* output)
{
	int i, j;
	i = j = 0;
	int newWidth = height;
	int newHeight = width;

	pixel newPixel;
	newPixel.red = newPixel.green = newPixel.blue = 255;
	newPixel.alpha = 255;

	for(j = 0; j < height; j++)
	{
		for(i = 0; i < width; i++)
		{
			int originalOffset = j*width + i;
			output[(height-j)+(i*height)] = image[j*width+i];
		}
	}


	return output;
}
