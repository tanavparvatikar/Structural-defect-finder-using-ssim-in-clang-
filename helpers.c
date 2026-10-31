#include "helpers.h"
#include <math.h>

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // to take average of each rgb then apply that value to all sets r g b
    // first i need to loop through each and every pixel - images - height var and width var , i
    // need 2 loops one for height and one for width then i call the fnx RGBTRIPLE
    // image[height][width]
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // i need to find avg of all values
            int temp;
            // temp var
            temp = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) /
                         (float) 3);
            // temp avg of the og values
            image[i][j].rgbtRed = temp;
            // red is assigned the og value
            // where is the avg with red being the og avg?? why am i assigning everyhting to reds
            // avg without including avg red into avg blue and avg green calcualations
            image[i][j].rgbtGreen = image[i][j].rgbtBlue = image[i][j].rgbtRed;
        }
    }
    return;
}
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gx_red = 0, gx_green = 0, gx_blue = 0;
            int gy_red = 0, gy_green = 0, gy_blue = 0;

            if (i - 1 >= 0 && j - 1 >= 0)
            {
                gx_red = (-1 * image[i - 1][j - 1].rgbtRed);
                gx_green = (-1 * image[i - 1][j - 1].rgbtGreen);
                gx_blue = (-1 * image[i - 1][j - 1].rgbtBlue);
                gy_red = (-1 * image[i - 1][j - 1].rgbtRed);
                gy_green = (-1 * image[i - 1][j - 1].rgbtGreen);
                gy_blue = (-1 * image[i - 1][j - 1].rgbtBlue);
            }
            if (i - 1 >= 0 && j >= 0)
            {
                gy_red = gy_red + (-2 * image[i - 1][j].rgbtRed);
                gy_green = gy_green + (-2 * image[i - 1][j].rgbtGreen);
                gy_blue = gy_blue + (-2 * image[i - 1][j].rgbtBlue);
            }
            if (i - 1 >= 0 && j + 1 < width)
            {
                gx_red = gx_red + (1 * image[i - 1][j + 1].rgbtRed);
                gx_green = gx_green + (1 * image[i - 1][j + 1].rgbtGreen);
                gx_blue = gx_blue + (1 * image[i - 1][j + 1].rgbtBlue);
                gy_red = gy_red + (-1 * image[i - 1][j + 1].rgbtRed);
                gy_green = gy_green + (-1 * image[i - 1][j + 1].rgbtGreen);
                gy_blue = gy_blue + (-1 * image[i - 1][j + 1].rgbtBlue);
            }
            if (i >= 0 && j - 1 >= 0)
            {
                gx_red = gx_red + (-2 * image[i][j - 1].rgbtRed);
                gx_green = gx_green + (-2 * image[i][j - 1].rgbtGreen);
                gx_blue = gx_blue + (-2 * image[i][j - 1].rgbtBlue);
            }
            if (i + 1 < height && j + 1 < width)
            {
                gx_red = gx_red + (1 * image[i + 1][j + 1].rgbtRed);
                gx_green = gx_green + (1 * image[i + 1][j + 1].rgbtGreen);
                gx_blue = gx_blue + (1 * image[i + 1][j + 1].rgbtBlue);
                gy_red = gy_red + (1 * image[i + 1][j + 1].rgbtRed);
                gy_green = gy_green + (1 * image[i + 1][j + 1].rgbtGreen);
                gy_blue = gy_blue + (1 * image[i + 1][j + 1].rgbtBlue);
            }
            if (i + 1 < height && j >= 0)
            {
                gy_red = gy_red + (2 * image[i + 1][j].rgbtRed);
                gy_green = gy_green + (2 * image[i + 1][j].rgbtGreen);
                gy_blue = gy_blue + (2 * image[i + 1][j].rgbtBlue);
            }
            if (i + 1 < height && j - 1 >= 0)
            {
                gx_red = gx_red + (-1 * image[i + 1][j - 1].rgbtRed);
                gx_green = gx_green + (-1 * image[i + 1][j - 1].rgbtGreen);
                gx_blue = gx_blue + (-1 * image[i + 1][j - 1].rgbtBlue);
                gy_red = gy_red + (1 * image[i + 1][j - 1].rgbtRed);
                gy_green = gy_green + (1 * image[i + 1][j - 1].rgbtGreen);
                gy_blue = gy_blue + (1 * image[i + 1][j - 1].rgbtBlue);
            }
            if (i < height && j + 1 < width)
            {
                gx_red = gx_red + (2 * image[i][j + 1].rgbtRed);
                gx_green = gx_green + (2 * image[i][j + 1].rgbtGreen);
                gx_blue = gx_blue + (2 * image[i][j + 1].rgbtBlue);
            }

            int redop = round(sqrt((gx_red * gx_red) + (gy_red * gy_red)));
            int greenop = round(sqrt((gx_green * gx_green) + (gy_green * gy_green)));
            int blueop = round(sqrt((gx_blue * gx_blue) + (gy_blue * gy_blue)));
            if (redop > 255)
                redop = 255;
            if (greenop > 255)
                greenop = 255;
            if (blueop > 255)
                blueop = 255;

            copy[i][j].rgbtRed = redop;
            copy[i][j].rgbtGreen = greenop;
            copy[i][j].rgbtBlue = blueop;
        }
    }
}



double ssim(int height, int width, RGBTRIPLE image[height][width],RGBTRIPLE reference[height][width])
{
    double window_total=0;
    const double C1=6.5025;
    const double C2=58.5225;


    //loop for checking , reference loop again before this 
    for(int i=0;(i*8)<height;i++)
    {
        for(int j=0;(j*8)<width;j++)
        {   
            const int N=64;
            double meana=0;
            double meanb=0;
            double ma1=0;
            double mb1=0;
            double va1=0;
            double vb1=0;
            double ab=0;
            double avab=0;
            double cova=0;
            double fva1=0;
            double fvb1=0;
            for(int k=0;k<8;k++)
            {
                for(int l=0;l<8;l++)
                {
                int temp1;
                int temp2;
                temp1=reference[i*8+k][j*8+l].rgbtRed;
                temp2=image[i*8+k][j*8+l].rgbtRed;
                ma1=ma1+temp1;
                mb1=mb1+temp2;
                ab=temp1*temp2+ab;
                fva1=fva1+(temp1*temp1);
                fvb1=fvb1+(temp2*temp2);
                    // loop finished final values gotten
                }
            }
            meana=(ma1)/N;
            meanb=(mb1)/N;
            va1=(fva1/N)-(meana)*(meana);
            vb1=(fvb1/N)-(meanb)*(meanb);
            avab=(ab/N);
            cova=avab-(meana*meanb);
            
            window_total=window_total+((2*meana*meanb+C1)*(2*cova+C2))/(((meana*meana)+(meanb*meanb)+C1)*(va1+vb1+C2));

        }

    }
window_total=window_total/((height/8)*(width/8));

return window_total;

}