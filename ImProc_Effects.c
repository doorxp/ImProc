// ImProc_Effects.c
// Image Processing Library
// Naming Semantics - All methods called from outside the library have leading capital letters
//                    All utility methods called from within the library have leading lowercase letters
//                    Utility methods should generally not be called from outside the library unless the
//                    implementer understands the function usage and memory allocations involved

#include <math.h>
#include <stdlib.h>
#include "ImProc_Effects.h"
#include "ImProc_Utils.h"
#include "ImProc_Edges.h"
#include "ImProc_Filters.h"

pixel* Cartoon(pixel* image, int lines, int colors, int width, int height, pixel* output)
{
	int i, length;
	length = width * height;
	pixel* copy = pixel_copy(image, width, height);
	Sobel_Edges(image, 0, 0, width, height, output);

	// custom threshold for multiplication
	for(i = 0; i < length; i++)
	{
		pixel oldPixel = output[i];
		if(oldPixel.red > lines)
			oldPixel.red = oldPixel.blue = oldPixel.green = 0;
		else
			oldPixel.red = oldPixel.blue = oldPixel.green = 1;
		output[i] = oldPixel;
	}

	Posterize(copy, colors, width, height, copy);

	for(i = 0; i < length;  i++)
	{
		pixel outputPixel = output[i];
		pixel copyPixel = copy[i];
		outputPixel.red *= copyPixel.red;
		outputPixel.blue *= copyPixel.blue;
		outputPixel.green *= copyPixel.green;
		output[i] = outputPixel;
	}

	free(copy);
	return output;
}

pixel* Posterize(pixel* image, int levels, int width, int height, pixel* output)
{
	int i;
	int length = width * height;
	int colorLevels[256];
	if (levels != 1)
		for (i = 0; i < 256; i++)
			colorLevels[i] = 255 * (levels*i / 256) / (levels-1);

	for(i = 0;  i < length; i++)
	{
		pixel newPixel = image[i];
		newPixel.red = colorLevels[newPixel.red];
		newPixel.blue = colorLevels[newPixel.blue];
		newPixel.green = colorLevels[newPixel.green];

		output[i] = newPixel;
	}

	return output;
}

pixel* Sketch(pixel* image, int threshold, int alpha, int width, int height, pixel* output)
{
	int i, j, k = 0;
	int length = width * height;

	// secondary gradient estimation method; maybe will try to get working at some point
	/*
	int grad_dist = 1;

	pixel* copy = malloc(length*sizeof(pixel));

	// step 1 - blur the image
	Fast_Blur_Gray(image, 3, width, height, copy);

	// step 2 - gradient estimation
	for (j = grad_dist; j < height-grad_dist; j++)
	{
		for(i = grad_dist; i < width-grad_dist; i++)
		{
			int offset = j*width+i;
			int max_r, max_l, max_u, max_d;
			max_r, max_l = max_u = max_d = 0;

			// compute gradient components
			for(k = 1; k <= grad_dist; k++)
			{
				int r = gradient(copy[offset], copy[offset+k], k);
				int l = gradient(copy[offset], copy[offset-k], k);
				int u = gradient(copy[offset], copy[(j-k)*width+i], k);
				int d = gradient(copy[offset], copy[(j+k)*width+i], k);

				if(abs(r) > max_r) max_r = abs(r);
				if(abs(l) > max_l) max_l = abs(l);
				if(abs(u) > max_u) max_u = abs(u);
				if(abs(d) > max_d) max_d = abs(d);
			}

			// compute horizontal gradient
			int max_h = max_r + max_l;
			int max_v = max_u + max_d;

			if(max_h > max_v)
				output[offset].red = output[offset].green = output[offset].blue = max_h;
			else
				output[offset].red = output[offset].green = output[offset].blue = max_v;
		}
	}


	// step 3 - gradient transform and thresholding
	// threshold image based on user parameter
	// step 2 - gradient estimation
	for (j = grad_dist; j < height-grad_dist; j++)
	{
		for(i = grad_dist; i < width-grad_dist; i++)
		{
			int offset = j*width+i;
			if(output[offset].red <= 3)
				output[offset].red = output[offset].blue = output[offset].green = 255;

			else
				output[offset].red = output[offset].blue = output[offset].green = 120 - output[offset].red;
		}
	}*/

	Sobel_Edges(image, 0, 0, width, height, output);


	for(i = 0; i < length; i++)
	{
		if(output[i].red <= threshold)
			output[i].red = output[i].blue = output[i].green = 255;

		else
			output[i].red = output[i].blue = output[i].green = alpha - output[i].red;
	}

	// step 4 - final smoothing
	Fast_Blur_Gray(output, 3, width, height, output);

	//free(copy);
	return output;
}

pixel* Static(pixel* image, int width, int height, pixel* output)
{
	Fast_Edges(image, 1, width, height, output);
	return output;
}

int gradient(pixel origin, pixel neighbor, int distance)
{
	// return estimate of gradient between pixels
	return (origin.red - neighbor.red)/distance;
}
