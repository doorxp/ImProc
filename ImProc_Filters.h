// ImProc_Filters.h
/*  
 *  Library Organization:
 *  The library is organized in a modular fashion to allow inclusion of selected functionality.
 *  Every implementation must include ImProc_Base.h as it contains the pixel struct and all macros.
 *  Beyond that, the implementation may include only those public API headers for which it needs functionality.
 *  Because the library is broken into modular pieces the public API headers/source contain inclusions for all 
 *  other library files they require for functionality. This means that the implementer should never need to 
 *  include the private library headers as they are already included in the public APIs when necessary. All 
 *  headers are protected by include guards to avoid multiple inclusion.
 *
 *  Public API Functionality Breakdown:
 *  ImProc_Base:      Contains all point operations for grayscale and RGB images
 *                    Contains all macros required by other public API modules
 *                    !! ImProc_Base MUST be included for all module implementations
 *  ImProc_Edges:     Contains all edge detection functionality
 *  ImProc_Filters:   Contains all spatial filter functionality
 *  ImProc_Histogram: Contains functionality for histogram calculation and equalization
 *  ImProc_Effects:	  Contains functionality for non-photorealistic effects
 *  ImProc_Color:	  Contains functionality for color component manipulation
 *  
 *  Note: All data structure and macro definitions are contained in ImProc_Base, ImProc_Utils, and ImProc_Convolve
 */

#ifndef FILTERS_H
#define FILTERS_H

#include <stdlib.h>
#include "ImProc_Convolve.h"
#include "ImProc_Base.h"

// linear filters
kernel_1d Make_Gaussian_1d_Kernel(double sigma);
pixel* Gaussian_Blur(pixel* image, double sigma, int width, int height, int type, pixel* output);
pixel* Blur_Or_Sharpen(pixel* image, float w, int width, int height, int type, pixel* output);
pixel* Fast_Blur_Gray(pixel* image, int size, int width, int height, pixel* output);
pixel* Fast_Blur_Color(pixel* image, int size, int width, int height, pixel* output);
pixel* Fast_Sharpen(pixel* image, int width, int height, pixel* output);
pixel* Unsharp_Masking(pixel* image, float sigma, float w, int width, int height, int type, pixel* output);

// non-linear filters
pixel* Max_Filter(pixel* image, int width, int height, pixel* output);
pixel* Min_Filter(pixel* image, int width, int height, pixel* output);
pixel* Median_Filter(pixel* image, int width, int height, pixel* output);

void sort(int arr[9], int beg, int end);

#endif
