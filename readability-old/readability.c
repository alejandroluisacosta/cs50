#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sent(string text);

int main(void)
{
    // Prompt the user to input a text
    string text = get_string("Text: ");

    // Count the letters of the text
    int letters = count_letters(text);

    // Count the words of the text
    int words = count_words(text);

    // Count the sentences of the text
    int sentences = count_sent(text);

    // Calculate the Coleman-Lieu index of the text
    float l = (100 * letters / words);
    float s = (100 * sentences / words);
    int coleman_lieu = round(0.0588 * l - 0.296 * s - 15.8);
    // Print the Coleman-Lieu index
    if (coleman_lieu < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (coleman_lieu >= 1 && coleman_lieu <= 16)
    {
        printf("Grade %i\n", coleman_lieu);
    }
    else if (coleman_lieu > 16)
    {
        printf("Grade 16+\n");
    }

}

// Function that counts the text's total ammount of letters
int count_letters(string text)
{
    // Counter varibable for letters
    int letters = 0;
    // Loop to count the letters
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

// Function that counts the text's total ammount of words
int count_words(string text)
{
    // Counter variable for words
    int words = 0;
    // Loop to count the words
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isspace(text[i]))
        {
            words++;
        }
    }
    return (words + 1);
}

// Function that counts the text's total ammount of sentences
int count_sent(string text)
{
    // Counter variable for sentences
    int sent = 0;
    // Loop to count the sentences
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            sent++;
        }
    }
    return sent;
}