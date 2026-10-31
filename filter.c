
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"

int main(void)
{
    double ssimval;
    int height = 480;
    int width = 640;
    int frame = 0;
    int calibration_frames = 30;

    RGBTRIPLE (*image)[width] = calloc(height, sizeof(*image));
    if (image == NULL)
    {
        return 7;
    }

    RGBTRIPLE (*reference)[width] = calloc(height, sizeof(*reference));
    if (reference == NULL)
    {
        free(image);
        return 7;
    }

    while (fread(image, sizeof(RGBTRIPLE), height * width, stdin) == height * width)
    {
        grayscale(height, width, image);

        if (frame < calibration_frames)
        {
            memcpy(reference, image, height * width * sizeof(RGBTRIPLE));
            fprintf(stderr, "\rCalibrating: %2d/%2d", frame + 1, calibration_frames);
        }
        else
        {
            ssimval = ssim(height, width, image, reference);

            if (frame % 15 == 0)
            {
                fprintf(stderr, "\rSSIM: %.4f    ", ssimval);
            }
        }

        edges(height, width, image);

        if (fwrite(image, sizeof(RGBTRIPLE), height * width, stdout) != height * width)
        {
            break;
        }

        fflush(stdout);
        frame++;
    }

    fprintf(stderr, "\n");

    free(reference);
    free(image);

    return 0;
}

