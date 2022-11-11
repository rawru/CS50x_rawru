#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_words(string text);
float count_letters(string text);
float count_sentences(string text);


int main(void)
{
    // Prompts user to input text
    string text = get_string("Text: ");

    // Count words
    int word = count_words(text);

    // Count letters
    float L = (count_letters(text) / word) * 100;

    // Count sentences
    float S = (count_sentences(text) / word) * 100;

    // Coleman-Liau index formula
    int index = round(((0.0588 * L) - (0.296 * S) - 15.8));

    // Outputs readability grade
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}


float count_letters(string text)
{
    int len = strlen(text), num = 0;

    // Simplify conditons by converting lowercase letters to uppercase
    for (int l = 0; l < len; l++)
    {
        text[l] = toupper(text[l]);
    }

    // Counts letters only
    for (int m = 0; m < len; m++)
    {
        if (text[m] >= 'A' && text[m] <= 'Z')
        {
            num++;
        }
    }

    return num;
}


float count_sentences(string text)
{
    int len = strlen(text), num = 0;

    // Counts the end punctuations
    // End punctuations shows that a sentence has ended hence the number of end punctuations = number of sentences
    for (int m = 0; m < len; m++)
    {
        if (text[m] == '.' || text[m] == '!' || text[m] == '?')
        {
            num++;
        }
    }

    return num;
}


int count_words(string text)
{
    // Takes the length of text
    int len = strlen(text);

    // Simplify conditons by converting lowercase letters to uppercase
    for (int l = 0; l < len; l++)
    {
        text[l] = toupper(text[l]);
    }

    // Number of words
    // Algorithm: if all non-space char before a space is a word,
    // then number of words = number of spaces + 1 (to add the last word which doesn't have a space after it)
    int num = 0, i = 0, cur = 0;
    while (i < len)
    {
        if (text[i] == ' ')
        {
            num++;
        }

        i++;
    }

    return num + 1;
}