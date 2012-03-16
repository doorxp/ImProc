#ifndef ADD_H_GUARD
#define ADD_H_GUARD

struct pixel{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  unsigned char alpha;
} pixel;

// point operations - grayscale
unsigned char* Invert_Pixels_Gray(unsigned char* image, int width, int height);
unsigned char* Modify_Contrast_Gray(unsigned char* image, int alpha, int width, int height);
unsigned char* Modify_Brightness_Gray(unsigned char* image, int alpha, int width, int height);
unsigned char* Threshold_Gray(unsigned char* image, int alpha, int width, int height);
unsigned char* Gamma_Corr_Gray(unsigned char* image, double alpha,  int width, int height);

// point operations - rgba
pixel* Invert_Pixels(pixel* image, int width, int height);
pixel* Modify_Contrast(pixel* image, int alpha, int width, int height);
pixel* Modify_Brightness(pixel* image, int alpha, int width, int height);
pixel* Threshold(pixel* image, int alpha, int width, int height);
pixel* Gamma_Corr(pixel* image, double alpha,  int width, int height);

// no differentiation for color vs gray here
// these methods should not be used real-time
// for grayscale simply set the gray value for one char per each channel
// true histogram equilization for color requires conversion to hsv - maybe in future?
pixel* Auto_Contrast(pixel* image, int width, int height);
pixel* Histogram_Eq(pixel* image, int width, int height);

// analysis
// Histogram for color images is three dimensional and too large for implementation; 2d options?
unsigned long* Histogram_Gray(unsigned char* image, int width, int height, unsigned long* histogram);
unsigned long** Histogram_RGB(pixel* image, int width, int height, unsigned long** histogram);
unsigned long* Histogram_RGB_toGray(pixel* image, int width, int height, unsigned long* histogram);
unsigned long* Cum_Histogram_Gray(unsigned char* image, int width, int height, unsigned long* histogram);
unsigned long** Cum_Histogram_RGB(pixel* image, int width, int height, unsigned long** histogram);
unsigned long* Cum_Histogram_RGB_toGray(pixel* image, int width, int height, unsigned long* histogram);

// utility methods
unsigned char* RGB_to_Gray_CharArray(pixel* image, int width, int height, unsigned char* gray_Image);
pixel* RGB_to_Gray_PixelArray(pixel* image, int width, int height);

#endif
