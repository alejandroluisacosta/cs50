#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
void print_character(char c);

int main(void)
{
    char *text;
    int i;

    text = get_string("Text: ");
    i = 0;
    while (text[i])
    {
        print_character(text[i]);
        i++;
    }
}

void print_character(char character)
{
    int i;

    int binary[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    i = 1;
    do
    {
        if (character % 2 == 1)
            binary[BITS_IN_BYTE - i] = 1;
        else
            binary[BITS_IN_BYTE - i] = 0;
        character /= 2;
        i++;
    }
    while (character > 0);
    i = 0;
    while (i < 8)
    {
        print_bulb(binary[i]);
        i++;
    }
    printf("\n");
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
