#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
int vote(char *name);
void print_winner(void);
int ft_strcmp(char *s1, char *s2);
void print_name(char *name);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (vote(name) != 1)
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
int vote(char *name)
{
    int i;

    i = 0;
    while (i < candidate_count)
    {
        if (ft_strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return (1);
        }
        i++;
    }
    return (0);
}

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] || s2[i])
    {
        if (s1[i] != s2[i])
            return (1);
        i++;
    }
    return (0);
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int i;
    int w_votes;

    i = 0;
    w_votes = 0;
    while (i < candidate_count)
    {
        if (candidates[i].votes > w_votes)
            w_votes = candidates[i].votes;
        i++;
    }
    i = 0;
    while (i < candidate_count)
    {
        if (candidates[i].votes == w_votes)
            print_name(candidates[i].name);
        i++;
    }
}

void print_name(char *name)
{
    int i;

    i = 0;
    while (name[i])
    {
        write(1, &name[i], 1);
        i++;
    }
    write(1, "\n", 1);
}
