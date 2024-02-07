#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Create a type of data for bytes
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    // If the program isn't correctly executed, return error
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Create an array to use it as buffer
    BYTE buffer[512];

    // Variable to establish JPEG block size
    int block_size = 512;

    //Open the file where the JPEGs are
    FILE *f = fopen(argv[1], "r");

    // If the provided file cannot be openned, return error
    if (f == NULL)
    {
        printf("Provided file %s could not be oppened", argv[1]);
        return 1;
    }

    // Variable to keep track of the amount of JPEGs that have been found
    int count = 0;

    // Char array to store the name of the new files I'll create
    char filename[8];

    // Create a pointer to a place in memory where to store the new files
    FILE *img = NULL;

    // Repeat until the end of that file:
    while (fread(buffer, 1, block_size, f) == block_size)
    {

        // Check for JPEG header
        if (buffer[0] == 0xff & buffer[1] == 0xd8 & buffer[2] == 0xff & (buffer[3] & 0xf0) == 0xe0)
        {
            // Increment JPEG count by one
            count++;
            // If it's the first JPEG found
            if (count == 1)
            {
                // Write the name of the new file into the string "filename"
                sprintf(filename, "%03i.jpg", (count - 1));
                // Open the new file
                img = fopen(filename, "w");
                // Write data into that new file
                fwrite(buffer, 1, block_size, img);
            }
            // If it's not the first JPEG
            else
            {
                // Close the finished JPEG
                fclose(img);
                // Write the new file name into "filename"
                sprintf(filename, "%03i.jpg", (count - 1));
                // Open file
                img = fopen(filename, "w");
                // Write data into file
                fwrite(buffer, 1, block_size, img);
            }
        }
        // If it's not the beginning of a JPEG
        else
        {
            // If the first JPEG has already been found
            if (count >= 1)
            {
                // Keep writing data relajao'
                fwrite(buffer, 1, block_size, img);
            }
        }
    }
    // Close remaining files
    fclose(f);
    fclose(img);
}