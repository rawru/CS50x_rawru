#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string arg);
string cipher(string text, int key);

int main(int argc, string argv[])
{
    // Cooperation errs: argc
    // no input
    if (argv[1] == NULL)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // > 1 input
    if (argv[2] != NULL)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Cooperation errs: input is non-int || negative
    if (only_digits(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // str input -> int input
    int key = atoi(argv[1]);

    // Text input
    string text = get_string("plaintext: ");

    // Output cipher
    printf("ciphertext: %s\n", cipher(text, key));
}

string cipher(string text, int key)
{
    // String length
    int len = strlen(text);

    // There are three mechanisms in rotating to letters:
    // Mechanism 1: If the current char + key > Z -> current char = [(char + key) - Z] + (A - 1) && check = true
    // Mechanism 2: If the current char + key < Z -> current char = char + key
    // Mechanism 3: If the current char is not a letter -> do nothing
    // Mechanism 1 repeats until its condition is false
    // The bool check is used such that only one if the mechanisms runs: if true then don't run mechanism 2, otherwise run mechanism 2
    bool check = false;
    for (int c = 0; c < len; c++)
    {
        // Restarts check value
        check = false;

        // ASCII scope overload fix
        if ((text[c] + key) > 127)
        {
            key %= 26;
        }

        // UPPERCASE
        if (text[c] >= 'A' && text[c] <= 'Z')
        {
            do
            {
                if ((text[c] + key) > 'Z')
                {
                    text[c] = ((text[c] + key) - 'Z') + 64;
                    check = true;
                }
            }
            while (text[c] > 'Z');

            if (check == false)
            {
                text[c] += key;
            }
        }

        // lowercase
        if (text[c] >= 'a' && text[c] <= 'z')
        {
            do
            {
                if ((text[c] + key) > 'z')
                {
                    text[c] = ((text[c] + key) - 'z') + 96;
                    check = true;
                }
            }
            while (text[c] > 'z');

            if (check == false)
            {
                text[c] += key;
            }
        }

        // Non-letter char: do nothing
    }

    return text;
}

bool only_digits(string arg)
{
    // String length
    int len = strlen(arg);

    // For each char: if is a char 0 -> 9, move to next char;
    // Otherwise, return false immediately
    for (int d = 0; d < len; d++)
    {
        if (arg[d] < '0' || arg[d] > '9')
        {
            return false;
        }
    }

    return true;
}