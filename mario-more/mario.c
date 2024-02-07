#include <cs50.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int height;
    int row;
    int spaces;
    int gap;
    int hashes;

    height = 0;
    while (height < 1 || height > 8)
        height = get_int("Height: ");
    row = 0;
    while (row < height)
    {
        spaces = row;
        while (spaces < height - 1)
        {
            write(1, " ", 1);
            spaces++;
        }
        hashes = 0;
        while (hashes < row)
        {
            write(1, "#", 1);
            hashes++;
        }
        write(1, "#", 1);
        write(1, "  ", 2);
        hashes = 0;
        while (hashes < row)
        {
            write(1, "#", 1);
            hashes++;
        }
        write(1, "#\n", 2);
        row++;
    }
    return (0);
}
