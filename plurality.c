#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

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
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Finds FIRST candidate to have the most amount of votes
    int most = 0, m_index = 0;
    for (int c = 0; c < candidate_count; c++)
    {
        if (candidates[c].votes > most)
        {
            most = candidates[c].votes;
            m_index = c;
        }
    }

    // Finds all other, if any, tied candidates
    int tie_index[candidate_count];
    for (int t = m_index; t < candidate_count; t++)
    {
        if (candidates[t].votes == most)
        {
            tie_index[t] = t + 1;
        }
    }


    // Prints all winners, tied or not
    for (int p = 0; p < candidate_count; p++)
    {
        if (tie_index[p] > 0)
        {
            printf("%s\n", candidates[tie_index[p] - 1].name);
        }
    }

    return;
}