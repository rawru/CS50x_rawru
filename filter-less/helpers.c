#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterates for all px in image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // finds the mean of the RGB values, set it to Blue; then copy Blue to Green and Red
            image[h][w].rgbtBlue = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.0);
            image[h][w].rgbtGreen = image[h][w].rgbtBlue;
            image[h][w].rgbtRed = image[h][w].rgbtBlue;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // iterates for all px in image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            BYTE originalBlue = image[h][w].rgbtBlue;
            BYTE originalGreen = image[h][w].rgbtGreen;
            BYTE originalRed = image[h][w].rgbtRed;

            // checks if the new values > 255: if true, set it to 255; else, keep the value
            if ((.272 * originalRed + .534 * originalGreen + .131 * originalBlue) > 255)
            {
                image[h][w].rgbtBlue = 255;
            }
            else
            {
                image[h][w].rgbtBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            }

            if ((.349 * originalRed + .686 * originalGreen + .168 * originalBlue) > 255)
            {
                image[h][w].rgbtGreen = 255;
            }
            else
            {
                image[h][w].rgbtGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            }

            if ((.393 * originalRed + .769 * originalGreen + .189 * originalBlue) > 255)
            {
                image[h][w].rgbtRed = 255;
            }
            else
            {
                image[h][w].rgbtRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            }
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // tmp buffers for swap
    RGBTRIPLE left, right;

    // iterates for all rows
    for (int h = 0; h < height; h++)
    {
        // since we are dealing with 2 symmetrical px, we only have to iterate until the center otherwise it swaps everything again back-to-place
        for (int w = 0; w < width / 2; w++)
        {
            left.rgbtBlue = image[h][w].rgbtBlue;
            left.rgbtGreen = image[h][w].rgbtGreen;
            left.rgbtRed = image[h][w].rgbtRed;

            right.rgbtBlue = image[h][width - 1 - w].rgbtBlue;
            right.rgbtGreen = image[h][width - 1 - w].rgbtGreen;
            right.rgbtRed = image[h][width - 1 - w].rgbtRed;

            image[h][w].rgbtBlue = right.rgbtBlue;
            image[h][w].rgbtGreen = right.rgbtGreen;
            image[h][w].rgbtRed = right.rgbtRed;

            image[h][width - 1 - w].rgbtBlue = left.rgbtBlue;
            image[h][width - 1 - w].rgbtGreen = left.rgbtGreen;
            image[h][width - 1 - w].rgbtRed = left.rgbtRed;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // an array to contain a copy of the image
    RGBTRIPLE copy[height][width];

    // copies the image px by px
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            copy[h][w].rgbtBlue = image[h][w].rgbtBlue;
            copy[h][w].rgbtGreen = image[h][w].rgbtGreen;
            copy[h][w].rgbtRed = image[h][w].rgbtRed;
        }
    }

    // grid 9
    for (int h = 1; h < height - 1; h++)
    {
        for (int w = 1; w < width - 1; w++)
        {
            image[h][w].rgbtBlue = round((copy[h - 1][w - 1].rgbtBlue + copy[h - 1][w].rgbtBlue + copy[h - 1][w + 1].rgbtBlue + copy[h][w -
                                          1].rgbtBlue +
                                          copy[h][w].rgbtBlue + copy[h][w + 1].rgbtBlue + copy[h + 1][w - 1].rgbtBlue + copy[h + 1][w].rgbtBlue +
                                          copy[h + 1][w + 1].rgbtBlue) / 9.0);
            image[h][w].rgbtGreen = round((copy[h - 1][w - 1].rgbtGreen + copy[h - 1][w].rgbtGreen + copy[h - 1][w + 1].rgbtGreen + copy[h][w -
                                           1].rgbtGreen +
                                           copy[h][w].rgbtGreen + copy[h][w + 1].rgbtGreen + copy[h + 1][w - 1].rgbtGreen + copy[h + 1][w].rgbtGreen +
                                           copy[h + 1][w + 1].rgbtGreen) / 9.0);
            image[h][w].rgbtRed = round((copy[h - 1][w - 1].rgbtRed + copy[h - 1][w].rgbtRed + copy[h - 1][w + 1].rgbtRed + copy[h][w -
                                         1].rgbtRed +
                                         copy[h][w].rgbtRed + copy[h][w + 1].rgbtRed + copy[h + 1][w - 1].rgbtRed + copy[h + 1][w].rgbtRed +
                                         copy[h + 1][w + 1].rgbtRed) / 9.0);
        }
    }

    // top 6
    for (int w = 1; w < width - 1; w++)
    {
        image[0][w].rgbtBlue = round((copy[0][w - 1].rgbtBlue + copy[0][w].rgbtBlue + copy[0][w + 1].rgbtBlue + copy[1][w - 1].rgbtBlue +
                                      copy[1][w].rgbtBlue +
                                      copy[1][w + 1].rgbtBlue) / 6.0);
        image[0][w].rgbtGreen = round((copy[0][w - 1].rgbtGreen + copy[0][w].rgbtGreen + copy[0][w + 1].rgbtGreen + copy[1][w - 1].rgbtGreen
                                       +
                                       copy[1][w].rgbtGreen + copy[1][w + 1].rgbtGreen) / 6.0);
        image[0][w].rgbtRed = round((copy[0][w - 1].rgbtRed + copy[0][w].rgbtRed + copy[0][w + 1].rgbtRed + copy[1][w - 1].rgbtRed +
                                     copy[1][w].rgbtRed +
                                     copy[1][w + 1].rgbtRed) / 6.0);
    }

    // right 6
    for (int h = 1; h < height - 1; h++)
    {
        image[h][width - 1].rgbtBlue = round((copy[h - 1][width - 2].rgbtBlue + copy[h][width - 2].rgbtBlue + copy[h + 1][width -
                                              2].rgbtBlue +
                                              copy[h - 1][width - 1].rgbtBlue + copy[h][width - 1].rgbtBlue + copy[h + 1][width - 1].rgbtBlue) / 6.0);
        image[h][width - 1].rgbtGreen = round((copy[h - 1][width - 2].rgbtGreen + copy[h][width - 2].rgbtGreen + copy[h + 1][width -
                                               2].rgbtGreen +
                                               copy[h - 1][width - 1].rgbtGreen + copy[h][width - 1].rgbtGreen + copy[h + 1][width - 1].rgbtGreen) / 6.0);
        image[h][width - 1].rgbtRed = round((copy[h - 1][width - 2].rgbtRed + copy[h][width - 2].rgbtRed + copy[h + 1][width - 2].rgbtRed +
                                             copy[h - 1][width - 1].rgbtRed + copy[h][width - 1].rgbtRed + copy[h + 1][width - 1].rgbtRed) / 6.0);
    }

    // bottom 6
    for (int w = 1; w < width - 1; w++)
    {
        image[height - 1][w].rgbtBlue = round((copy[height - 1][w - 1].rgbtBlue + copy[height - 1][w].rgbtBlue + copy[height - 1][w +
                                               1].rgbtBlue +
                                               copy[height - 2][w - 1].rgbtBlue + copy[height - 2][w].rgbtBlue + copy[height - 2][w + 1].rgbtBlue) / 6.0);
        image[height - 1][w].rgbtGreen = round((copy[height - 1][w - 1].rgbtGreen + copy[height - 1][w].rgbtGreen + copy[height - 1][w +
                                                1].rgbtGreen +
                                                copy[height - 2][w - 1].rgbtGreen + copy[height - 2][w].rgbtGreen + copy[height - 2][w + 1].rgbtGreen) / 6.0);
        image[height - 1][w].rgbtRed = round((copy[height - 1][w - 1].rgbtRed + copy[height - 1][w].rgbtRed + copy[height - 1][w +
                                              1].rgbtRed +
                                              copy[height - 2][w - 1].rgbtRed + copy[height - 2][w].rgbtRed + copy[height - 2][w + 1].rgbtRed) / 6.0);
    }

    // left 6
    for (int h = 1; h < height - 1; h++)
    {
        image[h][0].rgbtBlue = round((copy[h - 1][0].rgbtBlue + copy[h][0].rgbtBlue + copy[h + 1][0].rgbtBlue + copy[h - 1][1].rgbtBlue +
                                      copy[h][1].rgbtBlue +
                                      copy[h + 1][1].rgbtBlue) / 6.0);
        image[h][0].rgbtGreen = round((copy[h - 1][0].rgbtGreen + copy[h][0].rgbtGreen + copy[h + 1][0].rgbtGreen + copy[h - 1][1].rgbtGreen
                                       +
                                       copy[h][1].rgbtGreen + copy[h + 1][1].rgbtGreen) / 6.0);
        image[h][0].rgbtRed = round((copy[h - 1][0].rgbtRed + copy[h][0].rgbtRed + copy[h + 1][0].rgbtRed + copy[h - 1][1].rgbtRed +
                                     copy[h][1].rgbtRed +
                                     copy[h + 1][1].rgbtRed) / 6.0);
    }

    // tl
    image[0][0].rgbtBlue = round((copy[0][0].rgbtBlue + copy[0][1].rgbtBlue + copy[1][0].rgbtBlue + copy[1][1].rgbtBlue) / 4.0);
    image[0][0].rgbtGreen = round((copy[0][0].rgbtGreen + copy[0][1].rgbtGreen + copy[1][0].rgbtGreen + copy[1][1].rgbtGreen) / 4.0);
    image[0][0].rgbtRed = round((copy[0][0].rgbtRed + copy[0][1].rgbtRed + copy[1][0].rgbtRed + copy[1][1].rgbtRed) / 4.0);

    // tr
    image[0][width - 1].rgbtBlue = round((copy[0][width - 1].rgbtBlue + copy[0][width - 2].rgbtBlue + copy[1][width - 2].rgbtBlue +
                                          copy[1][width - 1].rgbtBlue) / 4.0);
    image[0][width - 1].rgbtGreen = round((copy[0][width - 1].rgbtGreen + copy[0][width - 2].rgbtGreen + copy[1][width - 2].rgbtGreen +
                                           copy[1][width - 1].rgbtGreen) / 4.0);
    image[0][width - 1].rgbtRed = round((copy[0][width - 1].rgbtRed + copy[0][width - 2].rgbtRed + copy[1][width - 2].rgbtRed +
                                         copy[1][width - 1].rgbtRed) / 4.0);

    // bl
    image[height - 1][0].rgbtBlue = round((copy[height - 1][0].rgbtBlue + copy[height - 1][1].rgbtBlue + copy[height - 2][0].rgbtBlue +
                                           copy[height - 2][1].rgbtBlue) / 4.0);
    image[height - 1][0].rgbtGreen = round((copy[height - 1][0].rgbtGreen + copy[height - 1][1].rgbtGreen + copy[height -
                                            2][0].rgbtGreen +
                                            copy[height - 2][1].rgbtGreen) / 4.0);
    image[height - 1][0].rgbtRed = round((copy[height - 1][0].rgbtRed + copy[height - 1][1].rgbtRed + copy[height - 2][0].rgbtRed +
                                          copy[height - 2][1].rgbtRed) / 4.0);

    // br
    image[height - 1][width - 1].rgbtBlue = round((copy[height - 1][width - 1].rgbtBlue + copy[height - 1][width - 2].rgbtBlue +
                                            copy[height - 2][width - 2].rgbtBlue + copy[height - 2][width - 1].rgbtBlue) / 4.0);
    image[height - 1][width - 1].rgbtGreen = round((copy[height - 1][width - 1].rgbtGreen + copy[height - 1][width - 2].rgbtGreen +
            copy[height - 2][width - 2].rgbtGreen + copy[height - 2][width - 1].rgbtGreen) / 4.0);
    image[height - 1][width - 1].rgbtRed = round((copy[height - 1][width - 1].rgbtRed + copy[height - 1][width - 2].rgbtRed +
                                           copy[height - 2][width - 2].rgbtRed + copy[height - 2][width - 1].rgbtRed) / 4.0);

    return;
}
