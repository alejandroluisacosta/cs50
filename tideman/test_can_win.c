#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool locked[9][9];
int candidate_count;
bool can_win(int winner, int loser);

int main(void)
{
    candidate_count = get_int("Candidates: ");
    int k;

    // Fill locked array with all falses
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
            locked[i][j] = false;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            k = 0;
            k = get_int("%d over %d: ", i, j);
            if (k == 1)
            {
                locked[i][j] = true;
            }
        }
        printf("\n");
    }
    if (can_win(0, 1) == true)
        printf("Yes\n");
    else
        printf("No\n");
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
