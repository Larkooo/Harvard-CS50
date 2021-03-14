#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // check usage
    if (argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    // check key
    int keyLength = strlen(key);
    if (keyLength != 26)
    {
        printf("Invalid key\n");
        return 1;
    }

    // key checks
    for (int i = 0; i < keyLength; i++)
    {
        char character = key[i];

        // check if character is not a letter
        if (!((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z')))
        {
            printf("Invalid key\n");
            return 1;
        }

        // check if letter repeated
        for (int n = 0; n < keyLength; n++)
        {
            if (n == i) continue;
            if (character == key[n])
            {
                printf("Invalid key\n");
                return 1;
            }
        }
    }

    string plaintext = get_string("plaintext: ");

    int plaintextLength = strlen(plaintext);

    // modifying the plaintext to ciphertext
    for (int i = 0; i < plaintextLength; i++)
    {
        char character = plaintext[i];
        char newCharacter;
        if (character >= 'a' && character <= 'z')
        {
            newCharacter = tolower(key[character - 97]);
        }
        else
        {
            newCharacter = key[character - 65];
        }
        plaintext[i] = newCharacter;
    }

    printf("ciphertext: %s\n", plaintext);

    return 0;
}