#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through rows of pixels
    for (int i = 0; i < height; i++)
    {
        // loop through pixels
        for (int p = 0; p < width; p++)
        {
            RGBTRIPLE* pixel = &image[i][p];
            const BYTE average = round((pixel->rgbtRed + pixel->rgbtGreen + pixel->rgbtBlue) / 3.0f);

            pixel->rgbtRed = average;
            pixel->rgbtGreen = average;
            pixel->rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through rows of pixels
    for (int i = 0; i < height; i++)
    {
        // loop through pixels
        for (int p = 0, half = width / 2; p < half; p++)
        {
            RGBTRIPLE tmp = image[i][p];
            const int opposite =  width - p - 1;
            image[i][p] = image[i][opposite];
            image[i][opposite] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // copy of image to do calculations on unblurred pixels
    RGBTRIPLE imagecp[height][width];

    // copying values to new array
    // loop through rows of pixels
    for (int i = 0; i < height; i++)
    {
        // loop through pixels
        for (int p = 0; p < width; p++)
        {
            // copy pixel to another array, to avoid doing calculations with blurred pixels
            imagecp[i][p] = image[i][p];
        }
    }

    // loop through rows of pixels
    for (int i = 0; i < height; i++)
    {
        // loop through pixels
        for (int p = 0; p < width; p++)
        {
            // close your eyes here, ugly way of getting neighbours just because im lazy
            RGBTRIPLE* pixel = &image[i][p];
            // middle pixel in count
            int nCount = 1;

            int avRed = pixel->rgbtRed;
            int avGreen = pixel->rgbtGreen;
            int avBlue = pixel->rgbtBlue;


            // top pixels
            if (i != 0)
            {
                avRed += imagecp[i - 1][p].rgbtRed;
                avGreen += imagecp[i - 1][p].rgbtGreen;
                avBlue += imagecp[i - 1][p].rgbtBlue;
                nCount++;

                // top left corner
                if (p != 0)
                {
                    avRed += imagecp[i - 1][p - 1].rgbtRed;
                    avGreen += imagecp[i - 1][p - 1].rgbtGreen;
                    avBlue += imagecp[i - 1][p - 1].rgbtBlue;
                    nCount++;
                }
                // top right corner
                if (p != width - 1)
                {
                    avRed += imagecp[i - 1][p + 1].rgbtRed;
                    avGreen += imagecp[i - 1][p + 1].rgbtGreen;
                    avBlue += imagecp[i - 1][p + 1].rgbtBlue;
                    nCount++;
                }
            }

            // left pixel
            if (p != 0)
            {
                avRed += imagecp[i][p - 1].rgbtRed;
                avGreen += imagecp[i][p - 1].rgbtGreen;
                avBlue += imagecp[i][p - 1].rgbtBlue;
                nCount++;
            }

            // right pixel
            if (p != width - 1)
            {
                avRed += imagecp[i][p + 1].rgbtRed;
                avGreen += imagecp[i][p + 1].rgbtGreen;
                avBlue += imagecp[i][p + 1].rgbtBlue;
                nCount++;
            }

            // bottom pixels
            if (i != height - 1)
            {
                avRed += imagecp[i + 1][p].rgbtRed;
                avGreen += imagecp[i + 1][p].rgbtGreen;
                avBlue += imagecp[i + 1][p].rgbtBlue;
                nCount++;

                // bottom left corner
                if (p != 0)
                {
                    avRed += imagecp[i + 1][p - 1].rgbtRed;
                    avGreen += imagecp[i + 1][p - 1].rgbtGreen;
                    avBlue += imagecp[i + 1][p - 1].rgbtBlue;
                    nCount++;
                }
                // bottom right corner
                if (p != width - 1)
                {
                    avRed += imagecp[i + 1][p + 1].rgbtRed;
                    avGreen += imagecp[i + 1][p + 1].rgbtGreen;
                    avBlue += imagecp[i + 1][p + 1].rgbtBlue;
                    nCount++;
                }
            }

            avRed = round((float) avRed / nCount);
            avGreen = round((float) avGreen / nCount);
            avBlue = round((float) avBlue / nCount);

            pixel->rgbtRed = avRed;
            pixel->rgbtGreen = avGreen;
            pixel->rgbtBlue = avBlue;

        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // copy of image to do calculations on unblurred pixels
    RGBTRIPLE imagecp[height][width];

    // copying values to new array
    // loop through rows of pixels
    for (int i = 0; i < height; i++)
    {
        // loop through pixels
        for (int p = 0; p < width; p++)
        {
            // copy pixel to another array, to avoid doing calculations with blurred pixels
            imagecp[i][p] = image[i][p];
        }
    }

    // loop through rows of pixels
    for (int i = 0; i < height; i++)
    {
        // loop through pixels
        for (int p = 0; p < width; p++)
        {
            RGBTRIPLE* pixel = &image[i][p];
            // neighbours
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    if (x == 0 && y == 0) continue;
                    RGBTRIPLE neighbour;
                    if ((p + x > width || p + x < 0) || (i + y > height || i + y < 0))
                    {
                        neighbour.rgbtRed = 0;
                        neighbour.rgbtGreen = 0;
                        neighbour.rgbtBlue = 0;
                    } 
                    else
                    {
                        neighbour = imagecp[i + y][p + x];
                    }
                }
            }
        }
    }
    return;
}
