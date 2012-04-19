// ImProc_Colors.c
// Image Processing Library
// Naming Semantics - All methods called from outside the library have leading capital letters
//                    All utility methods called from within the library have leading lowercase letters
//                    Utility methods should generally not be called from outside the library unless the
//                    implementer understands the function usage and memory allocations involved

#include <math.h>
#include <stdlib.h>
#include "ImProc_Utils.h"
#include "ImProc_Color.h"

// adjust pixel color values based on alpha input
pixel* Adjust_RGB(pixel* image, int r, int g, int b, int width, int height, pixel* output)
{
	int i = 0;
	int length = width * height;

	for(i; i < length; i++)
	{
		int newRed = image[i].red + r;
		int newGreen = image[i].green + g;
		int newBlue = image[i].blue + b;
		newRed = newRed > 255 ? 255 : newRed < 0 ? 0 : newRed;
		newGreen = newGreen > 255 ? 255 : newGreen < 0 ? 0 : newGreen;
		newBlue = newBlue > 255 ? 255 : newBlue < 0 ? 0 : newBlue;
		output[i].red = newRed;
		output[i].green = newGreen;
		output[i].blue = newBlue;
	}

	return output;
} 

pixel* Adjust_HSV(pixel* image, double h, double s, double v, int width, int height, pixel* output)
{
	int i = 0;
	int length = width * height;

	hsv_pixel* hsvImage = malloc(length*sizeof(hsv_pixel));
	Image_RGB_to_HSV(image, width, height, hsvImage);

	// modify channel values
	for(i; i < length; i++)
	{
		double newHue = hsvImage[i].hue + h;
		double newSat = hsvImage[i].sat + s;
		double newVal = hsvImage[i].val + v;
		newHue = newHue > 1 ? 1 : newHue < 0 ? 0 : newHue;
		newSat = newSat > 1 ? 1 : newSat < 0 ? 0 : newSat;
		newVal = newVal > 1 ? 1 : newVal < 0 ? 0 : newVal;
		hsvImage[i].hue = newHue;
		hsvImage[i].sat = newSat;
		hsvImage[i].val = newVal;
	}

	Image_HSV_to_RGB(hsvImage, width, height, output);
	free(hsvImage);

	return output;
}
