#include <cs50.h>
#include <stdio.h>
#include <unistd.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

typedef struct
{
    string name;
    int votes;
    int eliminated;
} candidate;

candidate candidates[MAX_CANDIDATES];

int vote(int voter, int rank, char *name);
int ft_strcmp(char *s1, char *s2);
void tabulate(void);
int print_winner(void);
int ft_round(int n);
void print_name(char *name);
int find_min(void);
int is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = 0;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (vote(i, j, name) != 1)
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    tabulate();
    for (int i = 0; i < candidate_count; i++)
    {
        printf("%s's votes: %d\n", candidates[i].name, candidates[i].votes);
    }
    int min = find_min();
    if (is_tie(min) == 1)
        printf("Tie\n");
    eliminate(min);
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == 1)
            printf("%s has been eliminated\n", candidates[i].name);
    }
    print_winner();
}

// Record preference if vote is valid
int vote(int voter, int rank, char *name)
{
    int i;

    i = 0;
    while (i < candidate_count)
    {
        if (ft_strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
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

void tabulate(void)
{
    int i;
    int j;

    i = 0;
    while (i < voter_count)
    {
        j = 0;
        while (j < candidate_count)
        {
            if (candidates[preferences[i][j]].eliminated == 0)
            {
                candidates[preferences[i][j]].votes++;
                break;
            }
            j++;
        }
        i++;
    }
}

int print_winner(void)
{
    int i;

    i = 0;
    while (i < candidate_count)
    {
        if (candidates[i].votes > voter_count / 2)
        {
            print_name(candidates[i].name);
            return (1);
        }
        i++;
    }
    return (0);
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

int find_min(void)
{
    int i;
    int less_votes;

    i = 0;
    less_votes = voter_count;
    while (i < candidate_count)
    {
        if (candidates[i].eliminated == 0)
        {
            if (candidates[i].votes < less_votes)
                less_votes = candidates[i].votes;
        }
        i++;
    }
    printf("Less votes: %d\n", less_votes);
    return (less_votes);
}

int is_tie(int min)
{
    int i;

    i = 0;
    while (i < candidate_count)
    {
        if (candidates[i].eliminated == 0)
        {
            if (candidates[i].votes > min)
                return (0);
        }
        i++;
    }
    return (1);
}

void eliminate(int min)
{
    int i;

    i = 0;
    while (i < candidate_count)
    {
        if (candidates[i].votes == min)
            candidates[i].eliminated = 1;
        i++;
    }
}
