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
pixel* Adjust_RGB(pixel* image, int channel, int alpha, int width, int height, pixel* output)
{
	int i = 0;
	int length = width * height;
	int newValue = 0;
	if(channel == R)
	{
		for(i; i < length; i++)
		{
			newValue = image[i].red + alpha;
			newValue = newValue > 255 ? 255 : newValue < 0 ? 0 : newValue;
			output[i].red = newValue;
		}
	}
	else if(channel == G)
	{
		for(i; i < length; i++)
		{
			newValue = image[i].green + alpha;
			newValue = newValue > 255 ? 255 : newValue < 0 ? 0 : newValue;
			output[i].green = newValue;
		}
	}
	else if(channel == B)
	{
		for(i; i < length; i++)
		{
			newValue = image[i].blue + alpha;
			newValue = newValue > 255 ? 255 : newValue < 0 ? 0 : newValue;
			output[i].blue = newValue;
		}
	}

	return output;
} 

pixel* Adjust_HSV(pixel* image, int channel, int alpha, int width, int height, pixel* output)
{
	float falpha = alpha/255.0;
	int i = 0;
	int length = width * height;

	// modify channel values
	if(channel == H && alpha != 0)
	{
		hsv_pixel* hsvImage = malloc(length*sizeof(hsv_pixel));
		Image_RGB_to_HSV(image, width, height, hsvImage);
		for(i; i < length; i++)
		{
			hsvImage[i].hue += falpha;
		}
		Image_HSV_to_RGB(hsvImage, width, height, output);
		free(hsvImage);
	}
	else if(channel == S)
	{
	}
	else if(channel == V)
	{
		for(i; i < length; i++)
		{
			int red = image[i].red + alpha;
			int green = image[i].green + alpha;
			int blue = image[i].blue + alpha;

			red = red > 255 ? 255 : red < 0 ? 0 : red;
			green = green > 255 ? 255 : green < 0 ? 0 : green;
			blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;

			output[i].red = red;
			output[i].green = green;
			output[i].blue = blue;
		}
	}

	return output;
}
