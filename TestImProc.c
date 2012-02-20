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
  printf("5 - Histogram\n");
  printf("Output will be written to \"output\"\n");

  char selection = getchar();
  char enter  = getchar();
  int sel;

  switch (selection) {
  case '1': Invert_Pixels(pixelVals, cols, rows);
    break;
  case '2': printf("Enter alpha value: ");
    scanf("%d", &sel);
    Modify_Brightness(pixelVals, sel, cols, rows);
    break;
  case '3': printf("Enter alpha value: ");
    scanf("%d", &sel);
    Modify_Contrast(pixelVals, sel, cols, rows);
    break;
  case '4': printf("Enter alpha value: ");
    scanf("%d", &sel);
    Threshold(pixelVals, sel, cols, rows);
    break;
  }

  fp = fopen("output", "w");

  for (i = 0; i < cols; i++)
    {
      for (j = 0; j < rows; j++)
	{
	  fprintf(fp, "%hu", *(pixelVals + (i*cols+j)));
	  fprintf(fp, "%s", " ");
	}
      fprintf(fp, "%s", "\n");
    }
  
  fclose(fp);
  free(pixelVals);
}
