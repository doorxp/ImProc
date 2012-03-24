// ImProc_utils.h
/*  
 *  Library Organization:
 *  The library is organized in a modular fashion to allow inclusion of selected functionality.
 *  Every implementation must include ImProc_Base.h as it contains the pixel struct and all macros.
 *  Beyond that, the implementation may include only those public API headers for which it needs functionality.
 *  The public API headers have the format ImProc_X.h where X is a capitol letter. The library headers have the
 *  format ImProc_x.h where x is a lowercase letter. Because the library is broken into modular pieces the 
 *  public API headers/source contain inclusions for all other library files they require for functionality.
 *  This means that the implementer should never need to include the private library headers as they are 
 *  already included in the public APIs when necessary. All headers are protected by include guards to avoid
 *  multiple inclusion.
 *
 *  Public API Functionality Breakdown:
 *  ImProc_Base:      Contains all point operations for grayscale and RGB images
 *                    Contains all macros required by other public API modules
 *                    !! ImProc_Base MUST be included for all module implementations
 *  ImProc_Edges:     Contains all edge detection functionality
 *  ImProc_Filters:   Contains all spatial filter functionality
 *  ImProc_Histogram: Contains functionality for histogram calculation and equilization
 *  
 *  Note: All data structure and macro definitions are contained in ImProc_Base, ImProc_utils, and ImProc_convolve
 */

#ifndef UTILS_H
#define UTILS_H

#include "ImProc_Base.h"

typedef struct pixelInt{
  int red;
  int green;
  int blue;
} pixelInt;

typedef struct hsv_pixel{
  double hue;
  double sat;
  double val;
} hsv_pixel;

// image transformation
pixel* rotate(pixel* image, int rtype, int width, int height, pixel* output);

// utility methods - type conversion, image combination, point operations
// caller must free memory for new copy of image
pixel* pixel_copy(pixel* image, int width, int height);
pixel* pixel_combine(pixel* image1, pixel* image2, int width, int height, int ctype);
pixel* pixel_pointOp(pixel* image, float alpha, int width, int height, int ctype);
pixel* pixelInt_to_pixel(pixelInt* image, int width, int height, pixel* newImage);
pixelInt* pixel_to_pixelInt(pixel* image, int width, int height, pixelInt* newImage);
pixelInt* pixelInt_copy(pixelInt* image, int width, int height);
pixelInt* pixelInt_combine(pixelInt* image1, pixelInt* image2, int width, int height, int ctype);
pixelInt* pixelInt_pointOp(pixelInt* image, float alpha, int width, int height, int ctype);

// utility methods - conversion
// RGB to grayscale conversion routines
int* RGB_to_Gray_IntArray(pixel* image, int width, int height, int* intArray);
pixel* IntArray_to_PixelArray(int* intArray, int width, int height, pixel* output);
pixel* RGB_to_Gray_PixelArray(pixel* image, int width, int height, pixel* output);

// RGB-HSV conversion routines
// These methods appear to convert back and forth with no loss; need more testing?
hsv_pixel* Image_RGB_to_HSV(pixel* rgb_image, int width, int height, hsv_pixel* hsv_image);
pixel* Image_HSV_to_RGB(hsv_pixel* hsv_image, int width, int height, pixel* rgb_image);
hsv_pixel pixel_rgb_to_hsv(pixel* rgb);
pixel pixel_hsv_to_rgb(hsv_pixel* hsv);

#endif
