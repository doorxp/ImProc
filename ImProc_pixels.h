// Nathan Wingert - u0687928
// Image Processing Library
// Naming Semantics - All methods called from outside the library have leading capital letters
//                    All utility methods called from within the library have leading lowercase letters
//                    Utility methods should generally not be called from outside the library unless the
//                    implementer understands the function usage and memory allocations involved

#ifndef ADD_H_GUARD
#define ADD_H_GUARD

typedef struct pixel{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  unsigned char alpha;
} pixel;

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

// point operations - grayscale
unsigned char* Invert_Pixels_Gray(unsigned char* image, int width, int height);
unsigned char* Modify_Contrast_Gray(unsigned char* image, int alpha, int width, int height);
unsigned char* Modify_Brightness_Gray(unsigned char* image, int alpha, int width, int height);
unsigned char* Threshold_Gray(unsigned char* image, int alpha, int width, int height);
unsigned char* Gamma_Corr_Gray(unsigned char* image, double alpha,  int width, int height);

// all point operations have been successfully tested in android except Modify_Alpha
// need a background image to display transparency in order to test Modify_Alpha 

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
// Auto_Contrast: only for gray?
// Histogram equilization will be different for gray vs color
// RGB hist_eq will require conversion to HSV, eq of value channel, conversion back to RGB
pixel* Auto_Contrast(pixel* image, int width, int height);
pixel* Histogram_Eq_Gray(pixel* image, int width, int height);
pixel* Histogram_Eq_Color(pixel* image, int width, int height);
*/

// analysis
// These methods have not been tested
unsigned long* Histogram_Lum(pixel* image, int width, int height, unsigned long* histogram);
unsigned long** Histogram_Color(pixel* image, int width, int height, unsigned long** histogram);
unsigned long* Cum_Histogram_Lum(pixel* image, int width, int height, unsigned long* histogram);
unsigned long** Cum_Histogram_Color(pixel* image, int width, int height, unsigned long** histogram);

// utility methods - conversion
// RGB to grayscale conversion routines
unsigned char* RGB_to_Gray_CharArray(pixel* image, int width, int height, unsigned char* gray_Image);
pixel* RGB_to_Gray_PixelArray(pixel* image, int width, int height);

// RGB-HSV conversion routines
// These methods appear to convert back and forth with no loss; need more testing?
// Any other cool way to use this?
hsv_pixel* Image_RGB_to_HSV(pixel* rgb_image, int width, int height, hsv_pixel* hsv_image);
pixel* Image_HSV_to_RGB(hsv_pixel* hsv_image, int width, int height, pixel* rgb_image);
hsv_pixel pixel_rgb_to_hsv(pixel* rgb);
pixel pixel_hsv_to_rgb(hsv_pixel* hsv);

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

// spatial filter methods
kernel_1d Make_Gaussian_1d_Kernel(double sigma);
pixel* Gaussian_Blur(pixel* image, double sigma, int width, int height, int type);
pixel* Blur_Or_Sharpen(pixel* image, float w, int width, int height, int type, pixel* output);
pixel* Fast_Blur(pixel* image, int width, int height);
pixel* Fast_Sharpen(pixel* image, int width, int height);
pixel* Unsharp_Masking(pixel* image, float sigma, float w, int width, int height, int type, pixel* output);

// edge detection
pixel* Gradient_Magnitude(pixel* image, double sigma, int width, int height);

// convolution methods
// all pixel arrays must be converted to and from pixelInt arrays for convolution
pixelInt* convolve_in_X(pixelInt* image, kernel_1d kernel, int width, int height, int d_type);
pixelInt* convolve_in_Y(pixelInt* image, kernel_1d kernel, int width, int height, int d_type);

/* 
// edge detection
gradient magnitude routine
sobel edge detection
prewitt edge detection
LoG detection

// morphological filters
erode
dilate
open
close
outline
skeletonize
*/

#endif
