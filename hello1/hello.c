#include <cs50.h>
#include <stdio.h>

int main(void)
{
    char *name;

    name = get_string("What's your name? ");
    printf("hello, %s\n", name);
}
