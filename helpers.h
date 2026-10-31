#include "bmp.h"
#include<math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]);

double ssim(int height, int width, RGBTRIPLE image[height][width],RGBTRIPLE reference[height][width]);

