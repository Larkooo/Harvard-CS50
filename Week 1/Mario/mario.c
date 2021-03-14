#include <stdio.h>
#include <cs50.h>

// defines
#define MIN 1
#define MAX 8

// declarations
int getHeight(void);
void drawBricks(int height);

int main(void) 
{
    // Ask the user for height
    int height = getHeight();
    
    drawBricks(height);
    return 0;
}

int getHeight(void) 
{
    int height;
    do 
    {
        height = get_int("Height: ");
    }
    while(height < MIN || height > MAX);
    return height;
}

void drawBricks(int height)
{
    // Iterate over columns, height
    for (int i = 1; i <= height; i++) 
    {
        // 3 iterations for the rows, this one is for the spaces before
        // drawing the bricks
        for (int n = 0; n < height - i; n++) 
        {
            printf(" ");
        }
        // drawing first line of bricks
        for (int n = 0; n < i; n++) 
        {
            printf("#");
        }
        // space between the second line of bricks
        printf("  ");
        // drawing the second line of bricks
        for (int n = 0; n < i; n++) 
        {
            printf("#");
        }
        // jump to the next line
        printf("\n");
    }
}