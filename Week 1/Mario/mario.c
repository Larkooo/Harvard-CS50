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
    while(height < MIN && height > MAX);
    return height;
}

void drawBricks(int height)
{
    for (int i = 0; i < height; i++) 
    {
        for (int n = 0; n < height - i; n++) 
        {
            printf(" ");
        }
        for (int n = 0; n < i; n++) 
        {
            printf("#");
        }
        printf(" ");
        for (int n = 0; n < i; n++) 
        {
            printf("#");
        }
        printf("\n");
    }
}