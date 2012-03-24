//  ImProc_Base.h
//  Nathan Wingert - u0687928
//  Image Processing Library
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

#ifndef BASE_H
#define BASE_H

#define MIN3(x,y,z)  ((y) <= (z) ?		\
		      ((x) <= (y) ? (x) : (y))	\
		      :				\
		      ((x) <= (z) ? (x) : (z)))

#define MAX3(x,y,z)  ((y) >= (z) ?		\
		      ((x) >= (y) ? (x) : (y))	\
		      :				\
		      ((x) >= (z) ? (x) : (z)))

#define FLOAT	0
#define INT 	1
#define PIXEL	3
#define ADD   0
#define SUB	  1
#define MUL	  2
#define DIV	  3
#define SQR   4
#define SQRT  5

typedef struct pixel{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  unsigned char alpha;
} pixel;

// point operations - grayscale
int* Invert_Pixels_Gray(int* image, int width, int height);
int* Modify_Contrast_Gray(int* image, int alpha, int width, int height);
int* Modify_Brightness_Gray(int* image, int alpha, int width, int height);
int* Threshold_Gray(int* image, int alpha, int width, int height);
int* Gamma_Corr_Gray(int* image, double alpha,  int width, int height);

// all point operations have been successfully tested in android except Modify_Alpha
// need a background image to display transparency in order to test Modify_Alpha 

// point operations - rgba - non-destructive
pixel* Invert_Pixels(pixel* image, int width, int height, pixel* output);
pixel* Modify_Contrast(pixel* image, int alpha, int width, int height, pixel* output);
pixel* Modify_Brightness(pixel* image, int alpha, int width, int height, pixel* output);
pixel* Threshold(pixel* image, int alpha, int width, int height, pixel* output);
pixel* Gamma_Corr(pixel* image, double alpha, int width, int height, pixel* output);
pixel* Modify_Alpha(pixel* image, int alpha, int width, int height, pixel* output);

#endif
