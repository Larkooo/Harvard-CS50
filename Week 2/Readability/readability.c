#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// declarations
int calculateGrade(int lCount, int wCount, int sCount);

int main(void)
{
    // Get text from user
    string text = get_string("Text: ");
    
    int lettersCount = 0;
    int wordsCount = 0;
    int sentencesCount = 0;

    // count 
    int strLength = strlen(text);
    for (int i = 0; i < strLength; i++)
    {
        // count letters
        char character = text[i];
        if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
        {
            lettersCount++;
        }
        // count words
        if (character == ' ' || i == (strLength - 1))
        {
            wordsCount++;
        }
        // count sentences
        if (character == '.' || character == '!' || character == '?')
        {
            sentencesCount++;
        }
    }

    #ifdef DEBUG // only for debug
    printf("%i letter(s)\n%i word(s)\n%i sentence(s)\n", lettersCount, wordsCount, sentencesCount);
    #endif

    int grade = calculateGrade(lettersCount, wordsCount, sentencesCount);
    if (grade > 16) 
    {
        printf("Grade 16+");
    } 
    else 
    {
        printf("Grade %i", grade);
    }
    printf("\n");
    
    return 0;
}


int calculateGrade(int lCount, int wCount, int sCount)
{
    float averageLetters = (lCount * 100) / wCount;
    float averageSentences = (sCount * 100) / wCount;
    // formula
    float index = 0.0588 * averageLetters - 0.296 * averageSentences - 15.8;
    return round(index);
}