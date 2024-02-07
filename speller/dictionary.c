// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash current word
    unsigned int h_index = hash(word);

    /* Access hash table at the index of the current word by creating a variable to be a
    "cursor", moving through a particular linked list while looking for said word*/
    node *cursor = table[h_index];

    // Loop through linked list searching for the word
    while (cursor != NULL)
    {
        // If the provided word matches the current word of the linked list
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        // If it doesn't match the first one, go to the next one
        else
        {
            // Give cursor the value of the next node
            cursor = cursor->next;
        }
    }
    // If no matches were found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Variable for current word's index in hash table
    unsigned int h_index = 0;

    // If it´s a one letter word
    if (word[1] == '\0')
    {
        h_index = (5 * (toupper(word[0]) - 'A')) % N;
    }

    // If it´s a two letter word
    else if (word[2] == '\0')
    {
        h_index = (5 * (toupper(word[0]) - 'A') + 10 * (toupper(word[1]) - 'A')) % N;
    }

    // If it´s a three-or-more letter word
    else
    {
        // If the second character is an apostrophe
        if (word[1] == 39)
        {
            h_index = (5 * (toupper(word[0]) - 'A') + 10 * word[1] + 15 * (toupper(word[2]) - 'A')) % N;
        }

        // If it isn't an apostrophe
        else
        {
            h_index = (5 * (toupper(word[0]) - 'A') + 10 * (toupper(word[1]) - 'A') + 15 * (toupper(word[2]) - 'A')) % N;
        }
    }

    // Return the index's value
    return h_index;
}


// Loads dictionary into memory, returning true if successful, else false
/* But before entering the actual function, create a variable to keep track of the amount of words in the dictionary
to use it later in the "size" function*/
int dic_word_count = 0;

// Now, the actual "load" function
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *d = fopen(dictionary, "r");

    // Check if the dictionary was correctly opened
    if (d == NULL)
    {
        free(table);
        printf("Dictionary could not be opened");
        return false;
    }

    // Create a buffer for the words to be read into from dictionary
    char buffer[LENGTH];

    // Create a variable to store the pointers for the new nodes
    node *n = NULL;

    // Create variable to keep track of the "bucket" index of the hash table where each node is going to be linked/stored
    unsigned int index = 0;

    // Read words from dictionary into buffer
    while (fscanf(d, "%s", buffer) != EOF)
    {
        // Create a new node for each word
        n = malloc(sizeof(node));

        // Increment the dictionary's word count
        dic_word_count++;

        // Check if memory was correctly allocated
        if (n == NULL)
        {
            // Print error message and return false
            printf("Error while allocating memory for dictionary's words");
            return false;
        }

        // If there was no problem and memory was correctly allocated
        else
        {
            // Copy the word from the buffer to the new node
            strcpy(n->word, buffer);

            // Calculate the bucket index where the node is going to be linked/stored
            index = hash(n->word);

            // Add the node to the beginning of the linked list by setting its "next" pointer to the current first node of the bucket
            n->next = table[index];

            // Change the pointer from the former first node to the new first node
            table[index] = n;
        }
    }
    fclose(d);
    // Return true if everything went ok
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // If the dictionary couldn't be loaded
    if (&load == false)
    {
        return 0;
    }

    // If the dictionary was correctly loaded
    else
    {
        return dic_word_count;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Set variable to be a "cursor" keeping track of the first non-freed element of the linked list
    node *cursor = NULL;

    // Set variable to be a temporal pointer that will free each node's memory
    node *tmp = NULL;

    // Loop through hash table
    for (int h_index = 0; h_index < N; h_index++)
    {
        // Give cursor the value of the current hash table's index
        cursor = table[h_index];
        // Loop through current index's linked list
        while (cursor != NULL)
        {
            // Give tmp the value of cursor
            tmp = cursor;
            // Move cursor to next position before freeing memory
            cursor = cursor->next;
            // Free memory
            free(tmp);
        }
        free(cursor);
    }
    return true;
}

