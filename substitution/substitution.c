#include <cs50.h>
#include <stdio.h>
#include <unistd.h>

int invalid_key(char *key);
int is_letter(char c);
void encrypt(char *text, char *ctext);
void ft_putchar(char c);
char *to_upper(char *text);

int main(int argc, char *argv[])
{
    char *text;
    int i;

    if (argc != 2)
    {
        write(1, "Usage: ./substitution key\n", 26);
        return (1);
    }
    if (invalid_key(argv[1]) == 1)
        return (1);
    text = get_string("plaintext:  ");
    encrypt(text, to_upper(argv[1]));
    write(1, "ciphertext: ", 12);
    i = 0;
    while (text[i])
    {
        ft_putchar(text[i]);
        i++;
    }
    write(1, "\n", 1);
    return (0);
}

int invalid_key(char *key)
{
    int i;
    int j;

    i = 0;
    while (key[i])
    {
        if (is_letter(key[i]) == 0)
        {
            write(1, "Error: Non-letter character in key\n", 35);
            return (1);
        }
        j = 0;
        while (j < i)
        {
            if (key[j] == key[i])
            {
                write(1, "Error: Repeated letter in key\n", 30);
                return (1);
            }
            j++;
        }
        i++;
    }
    if (i != 26)
    {
        printf("%i", i);
        write(1, "Error: Key must have 26 letters\n", 32);
        return (1);
    }
    return (0);
}

int is_letter(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return (1);
    return (0);
}

void encrypt(char *text, char *ctext)
{
    int i;
    int j;
    int found;
    char ptext[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    i = 0;
    while (text[i])
    {
        j = 0;
        found = 0;
        while (ptext[j] && found == 0)
        {
            if (text[i] >= 'A' && text[i] <= 'Z')
            {
                if (text[i] == ptext[j])
                {
                    text[i] = ctext[j];
                    found = 1;
                }
            }
            else if (text[i] >= 'a' && text[i] <= 'z')
            {
                if (text[i] - 32 == ptext[j])
                {
                    text[i] = ctext[j] + 32;
                    found = 1;
                }
            }
            j++;
        }
        i++;
    }
}

void ft_putchar(char c)
{
    write(1, &c, 1);
}

char *to_upper(char *text)
{
    int i;

    i = 0;
    while (text[i])
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            text[i] -= 32;
        }
        i++;
    }
    return (text);
}
