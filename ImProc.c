// Nathan Wingert - u0687928
// Image Processing Library Test Source

#include <stdio.h>

int[][] Invert_Pixels(int[][] image, int width, int height)
{
  int i,j;
  i = j = 0;
  
  for(i; i < width; i++)
    for(j; j < height; j++)
      image[i][j] = 255 - image[i][j]; 
}
