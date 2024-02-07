#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompts the user for name
    string name = get_string("What's your name?\n");

    // Prints hello + name on the screen
    printf("hello, %s\n", name);
}