// ImProc_convolve.h
// Image Processing Library
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

#ifndef CONVOLVE_H
#define CONVOLVE_H

#include "ImProc_Utils.h"

typedef struct kernel_1d{
  int* kernel_int;
  double* kernel_double;
  int length;
  int sum;
} kernel_1d;

// add 2d kernel later for morphological operators
/*
typedef struct kernel_2d{
  unsigned char* kernel;
  unsigned int width;
  unsigned int height;
  unsigned int sum;
}
*/

// convolution methods
// all pixel arrays must be converted to and from pixelInt arrays for convolution
pixelInt* convolve_in_X(pixelInt* image, kernel_1d kernel, int width, int height, int d_type);
pixelInt* convolve_in_Y(pixelInt* image, kernel_1d kernel, int width, int height, int d_type);
int* gray_convolve_in_X(int* image, kernel_1d kernel, int width, int height);
int* gray_convolve_in_Y(int* image, kernel_1d kernel, int width, int height);

#endif
