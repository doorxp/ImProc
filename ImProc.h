#ifndef ADD_H_GUARD
#define ADD_H_GUARD

// point operations
unsigned short* Invert_Pixels(unsigned short* image, int width, int height);
unsigned short* Modify_Contrast(unsigned short* image, int alpha, int width, int height);
unsigned short* Modify_Brightness(unsigned short* image, int alpha, int width, int height);
unsigned short* Threshold(unsigned short* image, int alpha, int width, int height);

// analysis
unsigned long* Histogram(unsigned short* image, int width, int height, unsigned long* histogram);

// feature detection

#endif
