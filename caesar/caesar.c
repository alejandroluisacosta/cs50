#include <cs50.h>
#include <stdio.h>
#include <unistd.h>

int only_digits(char *s);
int ft_atoi(char *s);
char *rotate(char *s, int k);
void ft_putchar(char s);

int main(int argc, char *argv[])
{
    int k;
    char *ptext;
    char *ctext;
    int i;

    if (argc != 2)
    {
        write(1, "Usage: ./caesar key\n", 20);
        return (1);
    }
    if (!argv[1])
    {
        write(1, "Usage: ./caesar key\n", 20);
        return (1);
    }
    if (only_digits(argv[1]) != 0)
    {
        write(1, "Usage: ./caesar key\n", 20);
        return (1);
    }
    k = ft_atoi(argv[1]);
    ptext = get_string("Plaintext:  ");
    ctext = rotate(ptext, k);
    write(1, "Ciphertext: ", 12);
    i = 0;
    while (ctext[i])
    {
        ft_putchar(ctext[i]);
        i++;
    }
    write(1, "\n", 1);
    return (0);
}

int only_digits(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (!(s[i] >= '0' && s[i] <= '9'))
        {
            write(1, "Usage: ./caesar key\n", 20);
            return (1);
        }
        i++;
    }
    return (0);
}

int ft_atoi(char *s)
{
    int i;
    int value;

    i = 0;
    value = 0;
    while (s[i])
    {
        value = 10 * value + (s[i] - '0');
        i++;
    }
    return (value);
}

char *rotate(char *s, int k)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] = (s[i] - 'A' + k) % 26;
            s[i] += 'A';
        }
        else if (s[i] >= 'a' && s[i] <= 'z')
        {
            s[i] = (s[i] - 'a' + k) % 26;
            s[i] += 'a';
        }
        i++;
    }
    return (s);
}

void ft_putchar(char s)
{
    write(1, &s, 1);
}
