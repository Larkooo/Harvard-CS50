// Implements a dictionary's functionality

#include <stdbool.h>
#include "dictionary.h"
#include <stdint.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// Aa
// Ab
// ..
// Ba
// Bb
const unsigned int N = 26 * 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    uint8_t count = 0;
    node* nextWord;
    node* wordNode;
    for (char* character = dictionary; *character != '\0'; character++)
    {
        
        if (*character == '\n') 
        {
            count = 0;
            wordNode->next = nextWord;
            table[*character * *(character + 1)] = &wordNode;
            wordNode = nextWord;
        }
        wordNode->word[count] = *character;
        count++;
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
