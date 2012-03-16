#ifndef ADD_H_GUARD
#define ADD_H_GUARD

typedef struct pixel{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  unsigned char alpha;
} pixel;

typedef struct hsv_pixel{
  double hue;
  double sat;
  double val;
} hsv_pixel;

// point operations - grayscale
unsigned char* Invert_Pixels_Gray(unsigned char* image, int width, int height);
unsigned char* Modify_Contrast_Gray(unsigned char* image, int alpha, int width, int height);
unsigned char* Modify_Brightness_Gray(unsigned char* image, int alpha, int width, int height);
unsigned char* Threshold_Gray(unsigned char* image, int alpha, int width, int height);
unsigned char* Gamma_Corr_Gray(unsigned char* image, double alpha,  int width, int height);

// point operations - rgba - destructive
pixel* Invert_Pixels_D(pixel* image, int width, int height);
pixel* Modify_Contrast_D(pixel* image, int alpha, int width, int height);
pixel* Modify_Brightness_D(pixel* image, int alpha, int width, int height);
pixel* Threshold_D(pixel* image, int alpha, int width, int height);
pixel* Gamma_Corr_D(pixel* image, double alpha, int width, int height);
pixel* Modify_Alpha_D(pixel* image, int alpha, int width, int height);

// point operations - rgba - non-destructive
// these are for slider bar type operations in GUIs
pixel* Modify_Contrast_ND(pixel* image, int alpha, int width, int height, pixel* output);
pixel* Modify_Brightness_ND(pixel* image, int alpha, int width, int height, pixel* output);
pixel* Threshold_ND(pixel* image, int alpha, int width, int height, pixel* output);
pixel* Gamma_Corr_ND(pixel* image, double alpha, int width, int height, pixel* output);
pixel* Modify_Alpha_ND(pixel* image, int alpha, int width, int height, pixel* output);

/*
// no differentiation for color vs gray here
// these methods should not be used real-time
// for grayscale simply set the gray value for one char per each channel
// true histogram equilization for color requires conversion to hsv - maybe in future?
pixel* Auto_Contrast(pixel* image, int width, int height);
pixel* Histogram_Eq_Gray(pixel* image, int width, int height);
pixel* Histogram_Eq_Color(pixel* image, int width, int height);
*/
// analysis
unsigned long* Histogram_Lum(pixel* image, int width, int height, unsigned long* histogram);
unsigned long** Histogram_Color(pixel* image, int width, int height, unsigned long** histogram);
unsigned long* Cum_Histogram_Lum(pixel* image, int width, int height, unsigned long* histogram);
unsigned long** Cum_Histogram_Color(pixel* image, int width, int height, unsigned long** histogram);

// utility methods
// RGB to grayscale conversion routines
unsigned char* RGB_to_Gray_CharArray(pixel* image, int width, int height, unsigned char* gray_Image);
pixel* RGB_to_Gray_PixelArray(pixel* image, int width, int height);
// RGB-HSV conversion routines
hsv_pixel* image_rgb_to_hsv(pixel* rgb_image, int width, int height, hsv_pixel* hsv_image);
hsv_pixel pixel_rgb_to_hsv(pixel* rgb);
pixel* image_hsv_to_rgb(hsv_pixel* hsv_image, int width, int height, pixel* rgb_image);
pixel pixel_hsv_to_rgb(hsv_pixel* hsv);

#endif
