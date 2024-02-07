#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

int count_letters(char *text);
int count_words(char *text);
int count_sentences(char *text);
void print_index(int *index_ptr);
void print_nbr(int nb);
void ft_putchar(char nb);

int main(void)
{
    char *text;
    int letters;
    int words;
    int sentences;
    int index;
    int *index_ptr;
    double L;
    double S;

    text = get_string("Text: ");
    letters = count_letters(text);
    words = count_words(text);
    sentences = count_sentences(text);
    L = 100 * (float) letters / (float) words;
    S = 100 * (float) sentences / (float) words;
    index = (int) round(0.0588 * L - 0.296 * S - 15.8);
    index_ptr = &index;
    print_index(index_ptr);
    return (0);
}

int count_letters(char *text)
{
    int i;
    int counter;

    i = 0;
    counter = 0;
    while (text[i])
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
            counter++;
        i++;
    }
    return (counter);
}

int count_words(char *text)
{
    int i;
    int counter;

    i = 0;
    counter = 0;
    while (text[i])
    {
        if (text[i] == ' ')
            counter++;
        i++;
    }
    if (counter == 0)
        return (0);
    return (counter + 1);
}

int count_sentences(char *text)
{
    int i;
    int counter;

    i = 0;
    counter = 0;
    while (text[i])
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
            counter++;
        i++;
    }
    return (counter);
}

void print_index(int *index_ptr)
{
    if (*index_ptr < 1)
        write(1, "Before Grade 1\n", 15);
    else if (*index_ptr >= 1 && *index_ptr <= 16)
    {
        write(1, "Grade ", 6);
        print_nbr(*index_ptr);
        write(1, "\n", 1);
    }
    else
        write(1, "Grade 16+\n", 10);
}

void print_nbr(int nb)
{
    if (nb >= 10)
        print_nbr(nb / 10);
    ft_putchar((nb % 10) + '0');
}

void ft_putchar(char nb)
{
    write(1, &nb, 1);
}
