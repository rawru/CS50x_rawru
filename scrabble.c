#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

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

    // Compares scores and outputs the winner (or if it's a tie)
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // Takes the length of the word
    int len = strlen(word);

    // Converts to uppercase
    for (int l = 0; l < len; l++)
    {
        word[l] = toupper(word[l]);
    }

    // Match the letter to its corresponding score
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        if (word[i] >= 'A' && word[i] <= 'Z')
        {
            // Uses uppercase A as a starting point (hence the need for convertion)
            // Example: A - A will give 0; which matches to the correct score in POINTS[]
            sum += POINTS[word[i] - 'A'];
        }
    }

    return sum;
}
