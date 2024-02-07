#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Promt user for height input between 1 and 8
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

// Print piramid
    // Outter loop for line jumps

    for (int i = 0; i < height; i++)
    {
        // Inner loop 1 for decreasing blank spaces
        for (int b = (height - (i + 1)); b > 0; b--)
        {
            printf(" ");
        }
        // Inner loop 2 for increasing hash symbols
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}