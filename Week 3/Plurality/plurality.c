#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // using a pointer to not copy the value but instead get the value itself so we can modify it 
        candidate *candidate = &candidates[i];
        if (strcmp(name, candidate->name) == 0)
        {
            candidate->votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool mostVotes = true;
        // no need to use a pointer in this case because we don't want to change any values
        candidate cand = candidates[i];
        // loop over all the candidates again to compare actual candidate to each of other ones
        for (int n = 0; n < candidate_count; n++)
        {
            // if same candidate, skip
            if (i == n)
            {
                continue;
            }

            candidate comparedCand = candidates[n];
            // the > is important here, if we want ties 
            if (comparedCand.votes > cand.votes)
            {
                mostVotes = false;
            }
        }
        if (mostVotes)
        {
            printf("%s\n", cand.name);
        }
    }
    return;
}

