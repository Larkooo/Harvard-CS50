#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        int candidate = ranks[i];
        // the + 1 is to skip current candidate
        for (int n = i + 1; n < candidate_count; n++)
        {
            int otherCandidate = ranks[n];
            preferences[candidate][otherCandidate]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // loop through the preferences, the first array
    for (int i = 0; i < candidate_count; i++)
    {
        // loop through the second array of the preferences
        for (int n = 0; n < candidate_count; n++)
        {
            // if n delta rank count is bigger then i is winner
            if (preferences[i][n] > preferences[n][i])
            {
                pair pair;
                pair.winner = i;
                pair.loser = n;

                // push the pair to the array
                pairs[pair_count] = pair;
                pair_count++;
            }
        }
    }
    // set the pair count to the correct count
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int pairWinner = pairs[i].winner;
        int pairLoser = pairs[i].loser;

        int strength = preferences[pairLoser][pairWinner];

        for (int n = 0; n < pair_count; n++)
        {
            int sPairWinner = pairs[n].winner;
            int sPairLoser = pairs[n].loser;

            int sStrength = preferences[sPairLoser][sPairWinner];

            if (sStrength > strength)
            {
                pair tmp = pairs[i];
                pairs[i] = pairs[n];
                pairs[n] = tmp;
            }
        }
    }
    return;
}

bool is_cycle(int from, int to)
{
    for (int n = 0; n < candidate_count; n++)
    {
        if (locked[to][n] == true)
        {
            if (n == from)
            {
                return true;
            }
            if (is_cycle(from, n))
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        pair fPair = pairs[i];
        int fPairWinner = fPair.winner;
        int fPairLoser = fPair.loser;

        if (!is_cycle(fPairWinner, fPairLoser))
            locked[fPairWinner][fPairLoser] = true;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool pointingTowards = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                pointingTowards = true;
                break;
            }
        }

        if (pointingTowards == false)
        {
            printf("%s\n", candidates[i]);
            break;
        }
    }
    return;
}