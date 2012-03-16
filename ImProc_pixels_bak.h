#ifndef ADD_H_GUARD
#define ADD_H_GUARD

struct pixel{
  char red;
  char green;
  char blue;
  char gray;
};

// point operations
struct pixel* Invert_Pixels(struct pixel* image, int width, int height);
struct pixel* Modify_Contrast(struct pixel* image, int alpha, int width, int height);
struct pixel* Modify_Brightness(struct pixel* image, int alpha, int width, int height);
struct pixel* Threshold(struct pixel* image, int alpha, int width, int height);

// analysis
unsigned long** Histogram(struct pixel* image, int width, int height, unsigned long** histogram);

// feature detection

#endif
