#include <stdio.h>
#include <stdlib.h>
#include "ImProc.h"

int main (int argc, char **argv)
{
  if(argc != 4)
    {
      printf("Invalid count for command-line arguments\n");
      abort();
    }

  short* pixelVals;
  unsigned long* histogram;
  int cols = strtol(argv[2], NULL, 10);
  int rows = strtol(argv[3], NULL, 10);
  int i,j;
  i = j = 0;

  pixelVals = (short*)malloc(rows * cols * sizeof(short*));

  FILE *fp;

  if((fp = fopen(argv[1], "r")) == NULL)
    {
      printf("Invalid pixel matrix\n");
      abort();
    }
    
  for (i = 0; i < cols; i++)
    {
      for (j = 0; j < rows; j++)
	{
	  fscanf(fp, "%hu", (pixelVals + (i*cols+j)));
	}
    }
  
  fclose(fp);

  printf("Image matrix loaded successfully\n");
  printf("1 - Invert Pixels\n");
  printf("2 - Brightness\n");
  printf("3 - Contrast\n");
  printf("4 - Thresholding\n");
  printf("5 - Auto-Contrast\n");
  printf("6 - Histogram Equilization\n");
  printf("7 - Gaussian Filter\n");
  printf("8 - Histogram\n");
  printf("9 - Cumulative Histogram\n");
  printf("Output will be written to \"output\"\n");

  int selection, sel;
  scanf("%d", &selection);
  char enter  = getchar();

  switch (selection) {
  case 1: 
    Invert_Pixels(pixelVals, cols, rows);
    break;
  case 2: 
    printf("Enter alpha value: ");
    scanf("%d", &sel);
    Modify_Brightness(pixelVals, sel, cols, rows);
    break;
  case 3:
    printf("Enter alpha value: ");
    scanf("%d", &sel);
    Modify_Contrast(pixelVals, sel, cols, rows);
    break;
  case 4: 
    printf("Enter alpha value: ");
    scanf("%d", &sel);
    Threshold(pixelVals, sel, cols, rows);
    break;
  case 5:
    Auto_Contrast(pixelVals, cols, rows);
    break;
  case 8: 
    histogram = (unsigned long*)malloc(256 * sizeof(long*));
    for(i = 0; i < 256; i++)
      histogram[i] = 0;
    Histogram(pixelVals, cols, rows, histogram);
    break;
  }

  fp = fopen("output", "w");

  if(selection < 8)
    {
      for (i = 0; i < cols; i++)
	{
	  for (j = 0; j < rows; j++)
	    {
	      fprintf(fp, "%hu", *(pixelVals + (i*cols+j)));
	      fprintf(fp, "%s", " ");
	    }
	  fprintf(fp, "%s", "\n");
	}
    }
  else
    {
      for(i = 0; i < 256; i++)
	{
	  fprintf(fp, "%lu", *(histogram + i));
	  fprintf(fp, "%s", " ");
	}
    }
  fclose(fp);
  free(pixelVals);
}
