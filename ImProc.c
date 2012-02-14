// Nathan Wingert - u0687928
// Image Processing Library Test Source

#include <stdio.h>

short** Invert_Pixels(short** image, int width, int height)
{
    int i,j;
    i = j = 0;
 
    for(i; i < width; i++)
    {
      for(j; j < height; j++)
        {
          image[i][j] = 255 - image[i][j];
        }
    }
    return image;
}

short** Modify_Contrast(short** image, int alpha, int width, int height)
{
    int i,j;
    i = j = 0;
 
    for(i; i < width; i++)
    {
      for(j; j < height; j++)
        {
          // compute new pixel data
          short newPixel = image[i][j] * alpha;

          // clamp pixel data to 0/255 (assuming 8 bit depth)
          if(newPixel > 255) image[i][j] = 255;
          else image[i][j] = newPixel;
        }
    }
    return image;
}

short** Modify_Brightness(short** image, int alpha, int width, int height)
{
    int i,j;
    i = j = 0;
 
    for(i; i < width; i++)
    {
      for(j; j < height; j++)
        {
          // compute new pixel data
          short newPixel = image[i][j] + alpha;

          // clamp pixel data to 0/255 (assuming 8 bit depth)
          if(newPixel > 255) image[i][j] = 255;
          else image[i][j] = newPixel;
        }
    }
    return image;
}

short** Threshold(short** image, int alpha, int width, int height)
{
    int i,j;
    i = j = 0;
 
    for(i; i < width; i++)
    {
      for(j; j < height; j++)
        {
          if(image[i][j] < alpha) image[i][j] = 0;
          else image[i][j] = 255;
        }
    }
    return image;
}

unsigned long* Histogram(short** image, int width, int height)
{
    unsigned long histogram[];    
    int i,j;
    i = j = 0;
 
    for(i; i < width; i++)
    {
      for(j; j < height; j++)
        {
          short k = image[i][j];
          histogram[k] = histogram[k] + 1;
        }
    }
    return histogram;
}

short** Auto_Contrast(short** image, int width, int height)
{
    int i,j;
    i = j = 0;

    // compute histogram for image
    unsigned long histogram = Histogram(image, width, height);

    for(i; i < width; i++)
    {
      for(j; j < height; j++)
        {
          // compute new pixel data
          short newPixel = image[i][j] * alpha;

          // clamp pixel data to 0/255 (assuming 8 bit depth)
          if(newPixel > 255) image[i][j] = 255;
          else image[i][j] = newPixel;
        }
    }
    return image;
}


