#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
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
        candidates[i].eliminated = false;
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
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int c = 0; c < candidate_count; c++)
    {
        // Compares if the input matches any of the candidates
        if (strcmp(candidates[c].name, name) == 0)
        {
            preferences[voter][rank] = c;
            return true;
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int c = 0, r = 0;
    while (c < candidate_count)
    {
        if (candidates[c].eliminated == false)
        {
            for (int v = 0; v < voter_count; v++)
            {
                // If candidate in current rank r for voter v is eliminated, move to the next non-eliminated candidate
                while (candidates[preferences[v][r]].eliminated == true)
                {
                    r++;
                }

                // If candidate in current rank r for voter v matches current candidate (index c): add one to candidates[c].votes
                if (preferences[v][r] == c)
                {
                    candidates[c].votes++;
                }

                // Resets r for each voter
                r = 0;
            }
        }

        c++;
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Finds for the candidate with most votes and their index
    int most = -1, first_index;
    for (int c = 0; c < candidate_count; c++)
    {
        if (candidates[c].votes > most)
        {
            most = candidates[c].votes;
            first_index = c;
        }
    }

    // Check if most votes is >50%: if true, prints winner and returns true
    if (most > (voter_count / 2))
    {
        printf("%s\n", candidates[first_index].name);
        return true;
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Sets the least number of votes to at number of voters + 1 (largest number least can be is voter_count / 2, but + 1 is safer!)
    int least = voter_count + 1;
    for (int c = 0; c < candidate_count; c++)
    {
        if (candidates[c].eliminated == false)
        {
            // Check if current candidate is less than least: if true, update least with current candidate vote count
            if (candidates[c].votes < least)
            {
                least = candidates[c].votes;
            }
        }
    }

    return least;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // If current candidate also has the least votes, mark current candidate as 1
    int tie[candidate_count];
    for (int c = 0; c < candidate_count; c++)
    {
        if (candidates[c].votes == min)
        {
            tie[c] = 1;
        }
    }

    // If current candidate is eliminated but isn't marked 1, mark the candidate 1
    for (int c = 0; c < candidate_count; c++)
    {
        if (tie[c] != 1)
        {
            if (candidates[c].eliminated == true)
            {
                tie[c] = 1;
            }
        }
    }

    // Counts all candidates marked with 1
    int tie_count = 0;
    for (int c = 0; c < candidate_count; c++)
    {
        if (tie[c] == 1)
        {
            tie_count++;
        }
    }

    // If there are as many candidates marked with 1 as there are candidates, all candidates must have tied
    if (tie_count >= candidate_count)
    {
        return true;
    }

    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int c = 0; c < candidate_count; c++)
    {
        // If current candidate has/also least votes, eliminate candidate
        if (candidates[c].votes == min)
        {
            candidates[c].eliminated = true;
        }
    }
    return;
}