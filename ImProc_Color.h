// ImProc_Color.h
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

#ifndef COLOR_H
#define COLOR_H

#include "ImProc_Base.h"

pixel* Adjust_RGB(pixel* image, int r, int g, int b, int width, int height, pixel* output);
pixel* Adjust_HSV(pixel* image, double h, double s, double v, int width, int height, pixel* output);

#endif
