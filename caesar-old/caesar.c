#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string s);
char rotate_letters(char c, int n);

int main(int argc, string argv[])
{
// Accept a single command-line argument that is a non-negative integer
    if (argc > 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
// If there's no command-line argument, print error message
    else if (argc == 1)
    {
        printf("Error: key number needed for encrypting\n");
        return 1;
    }
// If the command line argument isn't a decimal digit, print "Usage: ./caesar key"
    int command_test = only_digits(argv[1]);
    if (command_test == 1)
    {
        return 1;
    }

// Convert argv[1] into a int
    int key = atoi(argv[1]);

// Prompt user for plaintex
    string plaintext = get_string("Plaintext:  ");

// For each character in the plaintext
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        char cipher = rotate_letters(plaintext[i], key);
        // Print the ciphertext
        printf("%c", cipher);
    }
    printf("\n");
}

// Function to determine if the key has only digits
bool only_digits(string s)
{
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (isdigit(s[i]) == 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    return 0;
}

// Function to rotate the characters
char rotate_letters(char c, int n)
{
    // To determine if it's an alphabetic character
    if (isalpha(c))
    {
        // If it's uppercase
        if (isupper(c))
        {
            // Convert ASCII mapping value to alphabetic to apply the cipher formula
            c = ((c - 65) + n) % 26;
            // Re-convert to ASCII to return it to main
            return c + 65;
        }
        // If it's lowercase
        else if (islower(c))
        {
            c = ((c - 97) + n) % 26;
            return c + 97;
        }
    }
    else
    {
        return c;
    }
    return 0;
}