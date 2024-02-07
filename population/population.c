#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start;
    int end;
    int years;

    start = 0;
    while (start < 9)
        start = get_int("Start size: ");
    end = 0;
    while (end < start)
        end = get_int("End size: ");
    years = 0;
    while (start < end)
    {
        start = start + (start / 3) - (start / 4);
        years++;
    }
    printf("Years: %i\n", years);
    return (0);
}
