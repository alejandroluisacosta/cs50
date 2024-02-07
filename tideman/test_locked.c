#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Prototypes
void lock_pairs(void);
bool can_win(int winner, int loser);

// Pair and candidate count
int pair_count;
int candidate_count;

// Max number of candidates
#define MAX 9

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

pair pairs[MAX * (MAX - 1) / 2];


int main(void)
{
    pair_count = get_int("Number of pairs: ");
    candidate_count = get_int("Number of candidates: ");

    // Fill locked array with all falses
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
            locked[i][j] = false;
    }

    // Prompt user for pairs
    for (int i = 0; i < pair_count; i++)
    {
        pairs[i].winner = get_int("Pair %d's winner: ", i);
        pairs[i].loser = get_int("Pair %d's loser: ", i);
        printf("\n");
    }

    // Apply lock_pairs
    lock_pairs();
    return (0);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int i;

    i = 0;
    while (i < pair_count)
    {
        if (can_win(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            printf("Edge from %d to %d\n", pairs[i].winner, pairs[i].loser);
        }
        else
            printf("No edge from %d to %d\n", pairs[i].winner, pairs[i].loser);
        i++;
    }
}

// Function to recursively determine if edge can be locked without cycle
bool can_win(int winner, int loser)
{
    int i;
    bool draw_edge;

    i = 0;
    draw_edge = true;
    while (i < candidate_count)
    {
        if (locked[i][winner] == true)
        {
            if (i == loser)
            {
                draw_edge = false;
                return false;
            }
            else
            {
                if (!can_win(i, loser))
                    return false;
            }
        }
        i++;
    }
    return true;
}
