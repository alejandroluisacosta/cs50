#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
        write(1, "Player 1 wins!\n", 15);
    else if (score2 > score1)
        write(1, "Player 2 wins!\n", 15);
    else
        write(1, "Tie!\n", 5);
}

int compute_score(char *word)
{
    int i;
    int score;

    i = 0;
    score = 0;
    while (word[i])
    {
        if ((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z'))
        {
            if (word[i] >= 'a' && word[i] <= 'z')
                word[i] -= 32;
            score += POINTS[word[i] - 65];
        }
        i++;
    }
    return (score);
}
