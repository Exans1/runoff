#include <cs50.h>
#include <stdio.h>
#include <strings.h>

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
int indexboolArr[MAX];


int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool Beatit(int winner, int loser);

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
    // TODO
    for(int i = 0; i < candidate_count; i++)
    {
        if(strcasecmp(name,candidates[i])==0)
        {
            ranks[rank] = i;
            //printf("%i\n", ranks[i]);
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            if(i < j )
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }

for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf(" %i", preferences[i][j]);

        }
        printf("\n");
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int pc = 0;
    for(int j = 0; j < candidate_count; j++)
        {
            for(int i = 0; i < candidate_count; i++)
            {
                if (preferences[i][j] > preferences[j][i] && j < i)
                {
                    pairs[pc].winner = i;
                    pairs[pc].loser = j;
                    pc++;
                }
                if (preferences[i][j] <= preferences[j][i] && j < i)
                {
                    if(preferences[i][j] < preferences[j][i] && j < i)
                        {
                            pairs[pc].winner = j;
                            pairs[pc].loser = i;
                            pc++;
                        }
                }
            }
        }
        pair_count = pc;
        for (int i = 0; i < pc; i++)
        {
            // printf("pairs.winner %i: %i\n", i +1, pairs[i].winner);
            // printf("pairs.loser %i: %i\n", i + 1, pairs[i].loser);
            // printf("\n");
        }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    typedef struct
{
    int win;
    int los;
    int hnum;
}
pairL;
pairL ogPair[pair_count];
int hnumTempH[pair_count];
int hnumTempL[pair_count];
int hnumTemp[pair_count];

    // printf("Winer: ");
    //     for (int i = 0; i < pair_count; i++)
    // {
    //     printf("%i ", pairs[i].winner);
    // }
    // printf("\n");
    // printf("Loser: ");
    // for (int i = 0; i < pair_count; i++)
    // {
    //     printf("%i ", pairs[i].loser);
    // }
    // printf("\n");
    // printf("H num: ");
    for (int i = 0; i < pair_count; i++)
    {
        hnumTempH[i]=preferences[pairs[i].winner][pairs[i].loser];
        hnumTempL[i]=preferences[pairs[i].loser][pairs[i].winner];

    }


for(int i = 0; i < pair_count; i++)
{
    hnumTemp[i] = hnumTempH[i] - hnumTempL[i];
    ogPair[i].win = pairs[i].winner;
    ogPair[i].los = pairs[i].loser;
    ogPair[i].hnum = hnumTemp[i];
    // printf("%i ", hnumTemp[i]);
}
//  printf("\n");

int temp = 0;
int boolTemp[pair_count];
pairL sWin[pair_count];
for(int i = 0; i < pair_count; i++)
{
    boolTemp[i] = 1;
    sWin[i].win = 0;
    sWin[i].los = 0;
    sWin[i].hnum = 0;
}

int Largest = preferences[pairs[0].winner][pairs[0].loser];

for(int i = 0; i < candidate_count; i++)
            {
                if(Largest < preferences[pairs[i].winner][pairs[i].loser])
                {
                    Largest = preferences[pairs[i].winner][pairs[i].loser];
                }
            }

while(temp < pair_count)
{
    for(int i = 0; i < pair_count; i++)
    {
        if(Largest == preferences[pairs[i].winner][pairs[i].loser] && boolTemp[i] == 1)
        {
            sWin[temp] = ogPair[i];
            boolTemp[i] = 0;
            temp++;
        }
    }
            Largest--;
}

    printf("Sorted win:  ");
    for (int i = 0; i < pair_count; i++)
    {
        printf("%i ", sWin[i].win);
    }
    printf("\n");
    printf("Sorted los:  ");
    for (int i = 0; i < pair_count; i++)
    {
        printf("%i ", sWin[i].los);
    }
    printf("\n");
    printf("Sorted diff: ");
    for (int i = 0; i < pair_count; i++)
    {
        printf("%i ", sWin[i].hnum);
    }
    printf("\n");

for(int i = 0; i < pair_count; i++)
{
    pairs[i].winner = sWin[i].win;
    pairs[i].loser = sWin[i].los;
    hnumTemp[i] = sWin[i].hnum;
}

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    // TODO

     for(int z = 0; z < candidate_count; z++)
        {
            indexboolArr[z] = 0;
        }

    locked[pairs[0].winner][pairs[0].loser] = true;

    for(int i = 1; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = Beatit(pairs[i].winner,pairs[i].loser);
    }


    printf("\n");
    printf("--- --- -- Locked -- --- ---\n");
for(int i = 0; i < candidate_count; i++)
{
    for(int j = 0; j < candidate_count; j++)
    {
        if(j==0)
        {
            printf("      ");
        }
        printf(" %i ",locked[i][j]);
    }
    printf("\n");
}
printf("--- True = 1 | False = 0 ---\n\n");
    printf("\n");
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    {
    // Winner is the candidate with no arrows pointing to them
    for (int i = 0; i < candidate_count; i++)
    {
        int false_count = 0;        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                false_count++;
                if (false_count == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    }

    return;
}

bool Beatit(int winner, int loser)
{

// anything with z is for resetting array
        indexboolArr[winner] = 1;

if(winner <= candidate_count)
{
            for(int i = 0; i< pair_count; i++)
            {
                int tempc = 0;
                if(locked[loser][i] == 1 && loser != i)
                {
                    indexboolArr[loser]++;
                    Beatit(loser, i);
                }
                else if(locked[loser][i] == 0 && loser != i)
                {
                    tempc++;
                }
                int count = 0;
                for( int j = 0; j < candidate_count; j ++)
                {
                    if(indexboolArr[j] >= 1)
                    {
                        count++;
                    }
                }
                if(count == candidate_count )
                {

                    // for(int z = 0; z < candidate_count; z++)
                    //     {
                    //         if( z != loser && z!= winner)
                    //         indexboolArr[z] = 0;
                    //     }

                        return false;
                    }
                if(tempc == pair_count)
                {
                    for(int z = 0; z < candidate_count; z++)
                    {
                        indexboolArr[z] = 0;
                    }

                    return true;
                }
            }

        for(int z = 0; z < candidate_count; z++)
        {
            indexboolArr[z] = 0;
        }
}
        return true;
}
