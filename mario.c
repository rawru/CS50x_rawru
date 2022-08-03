#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompts for height and repeats if input is < 1 || > 8.
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Each row has a height-amount of columns.
    // Since we start printing at the top, there will be 1 block and height - 1 spaces.
    int spc = height - 1, blck = 1;

    // loop: go to next line.
    for (int h = 0; h < height; h++)
    {
        // loop: prints spaces.
        for (int i = 0; i < spc; i++)
        {
            printf(" ");
        }
        // loop: prints block
        for (int b = 0; b < blck; b++)
        {
            printf("#");
        }
        // next line -> parent for loop.
        printf("\n");
        // Converts the last space to a block.
        spc--;
        blck++;
    }
}