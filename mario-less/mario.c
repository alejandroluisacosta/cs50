#include <cs50.h>
#include <unistd.h>

int main(void)
{
    int height;
    int i;
    int j;
    int k;

    height = 0;
    while (height < 1 || height > 8)
        height = get_int("Height: ");
    i = 0;
    while (i < height)
    {
        j = i;
        while (j < height - 1)
        {
            write(1, " ", 1);
            j++;
        }
        k = 0;
        while (k < i)
        {
            write(1, "#", 1);
            k++;
        }
        write(1, "#\n", 2);
        i++;
    }
    return (0);
}
