#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float Red = image[i][j].rgbtRed;
            float Green = image[i][j].rgbtGreen;
            float Blue = image[i][j].rgbtBlue;
            int average = round(Red + Green + Blue) / 3 + .5;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sred =
                round(.393 * (float) image[i][j].rgbtRed + .769 * (float) image[i][j].rgbtGreen +
                      .189 * (float) image[i][j].rgbtBlue);
            if (sred > 255)
                sred = 255;
            int sgreen =
                round(.349 * (float) image[i][j].rgbtRed + .686 * (float) image[i][j].rgbtGreen +
                      .168 * (float) image[i][j].rgbtBlue);
            if (sgreen > 255)
                sgreen = 255;
            int sblue =
                round(.272 * (float) image[i][j].rgbtRed + .534 * (float) image[i][j].rgbtGreen +
                      .131 * (float) image[i][j].rgbtBlue);
            if (sblue > 255)
                sblue = 255;
            image[i][j].rgbtRed = sred;
            image[i][j].rgbtGreen = sgreen;
            image[i][j].rgbtBlue = sblue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE storage = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = storage;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE storage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            storage[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Red, Blue, Green;
            Red = Blue = Green = 0;
            float counter = 0;
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentX = i + x;
                    int currentY = j + y;
                    if (currentX < 0 || currentX > (height - 1) || currentY < 0 ||
                        currentY > (width - 1))
                    {
                        continue;
                    }
                    Red += image[currentX][currentY].rgbtRed;
                    Green += image[currentX][currentY].rgbtGreen;
                    Blue += image[currentX][currentY].rgbtBlue;
                    counter++;
                }
                storage[i][j].rgbtRed = round(Red / counter);
                storage[i][j].rgbtGreen = round(Green / counter);
                storage[i][j].rgbtBlue = round(Blue / counter);
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = storage[i][j].rgbtRed;
            image[i][j].rgbtGreen = storage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = storage[i][j].rgbtBlue;
        }
    }
    return;
}
