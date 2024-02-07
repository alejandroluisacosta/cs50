#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through image's rows of pixels
    for (int row = 0; row < height; row++)
    {
        // Loop through each pixel of a row
        for (int pixel = 0; pixel < width; pixel++)
        {
            // Calculate average of the average value for each BGR triplet and store it in variable "avg"
            float avg = round((image[row][pixel].rgbtBlue + image[row][pixel].rgbtGreen + image[row][pixel].rgbtRed) / 3.0);
            // Give each component of the pixel's triplet the average value
            image[row][pixel].rgbtBlue = avg;
            image[row][pixel].rgbtGreen = avg;
            image[row][pixel].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through image's rows of pixels
    for (int row = 0; row < height; row++)
    {
        // Loop through each pixel of a row
        for (int pixel = 0; pixel < width; pixel++)
        {
            // Save the original value of Blue, Green and Red into separate variables
            const int org_B = image[row][pixel].rgbtBlue;
            const int org_G = image[row][pixel].rgbtGreen;
            const int org_R = image[row][pixel].rgbtRed;
            // Update the pixel's Blue value using the sepia formula and capping it to 255
            int new_B = round((0.272 * org_R) + (0.534 * org_G) + (0.131 * org_B));
            if (new_B > 255)
            {
                image[row][pixel].rgbtBlue = 255;
            }
            else
            {
                image[row][pixel].rgbtBlue = new_B;
            }
            // Update the pixel's Green value using the sepia formula and capping it to 255
            int new_G = round((0.349 * org_R) + (0.686 * org_G) + (0.168 * org_B));
            if (new_G > 255)
            {
                image[row][pixel].rgbtGreen = 255;
            }
            else
            {
                image[row][pixel].rgbtGreen = new_G;
            }
            // Update the pixel's Red value using the sepia formula and capping it to 255
            int new_R = round((0.393 * org_R) + (0.769 * org_G) + (0.189 * org_B));
            if (new_R > 255)
            {
                image[row][pixel].rgbtRed = 255;
            }
            else
            {
                image[row][pixel].rgbtRed = new_R;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through image's rows of pixels
    for (int row = 0; row < height; row++)
    {
        // Variable that defines the half of the image's width
        int width_half = width / 2;
        // Loop through the row's first half of pixels
        for (int pixel = 0; pixel < width_half; pixel++)
        {
            // Break the loop when you reach the half of the width
            if (pixel >= width_half)
            {
                return;
            }
            else
            {
                //Temporal variable to store the value of one of the pixels and make the swapping possible
                RGBTRIPLE tmp;
                // Swap that thing up
                tmp = image[row][pixel];
                image[row][pixel] = image[row][width - 1 - pixel];
                image[row][width - 1 - pixel] = tmp;

            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of image[][]
    RGBTRIPLE copy[height][width];
    // Loop through image's rows
    for (int copy_row = 0; copy_row < height; copy_row++)
    {
        // Loop through image's columns
        for (int copy_column = 0; copy_column < width; copy_column++)
        {
            // Write the R-G-B values of image[][] into copy[][]
            copy[copy_row][copy_column] = image[copy_row][copy_column];
        }
    }
    // Bluring process begins:

    // Variables for new sums of R-G-B
    float new_blue = 0;
    float new_green = 0;
    float new_red = 0;
    // Loop through image's rows of pixels
    for (int row = 0; row < height; row++)
    {
        // Variables for the rows above and under each pixel
        int above_row = row - 1;
        int under_row = row + 1;
        // Loop through each row's pixels
        for (int pixel = 0; pixel < width; pixel++)
        {
            // Variables for the columns before and after each pixel
            int before_col = pixel - 1;
            int after_col = pixel + 1;
            // Variable to keep track of the ammount of pixels that are being used to average the new B-G-R for the current pixel
            int qty = 0;
            // Loop through adjacent rows of the current pixel to do the average
            for (int avg_row = above_row; avg_row <= under_row; avg_row++)
            {
                // Loop through adjacent columns
                for (int avg_col = before_col; avg_col <= after_col; avg_col++)
                {
                    if (avg_row < 0 || avg_row >= height || avg_col < 0 || avg_col >= width)
                    {
                        continue;
                    }
                    else
                    {
                        // Add up all the values from adjacent pixels' R-G-B
                        new_blue += copy[avg_row][avg_col].rgbtBlue;
                        new_green += copy[avg_row][avg_col].rgbtGreen;
                        new_red += copy[avg_row][avg_col].rgbtRed;
                        qty++;
                    }
                }
            }
            // Average those values using qty
            image[row][pixel].rgbtBlue = round(new_blue / qty);
            image[row][pixel].rgbtGreen = round(new_green / qty);
            image[row][pixel].rgbtRed = round(new_red / qty);
            // Restart count for next iteration
            qty = 0;
            new_blue = 0;
            new_green = 0;
            new_red = 0;
        }
    }
    return;
}
