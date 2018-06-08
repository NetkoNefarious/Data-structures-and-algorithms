#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 100

int mem[2][2][2][2], mem2[2][2][2][2];
int queue[MAXSIZE] = {0};
int start = 0, end = 0;

void push(int x)
{
    queue[end++] = x;
    end %= MAXSIZE;
}

int pop()
{
    int x = queue[start++];
    start %= MAXSIZE;
    return x;
}

void PrintState(int wolf, int sheep, int cabbage, int farmer)
{
    char l_bank[5] = "wscf";
    char r_bank[5] = "    ";

    if (!wolf)
        l_bank[0] ^= r_bank[0] ^= l_bank[0] ^= r_bank[0];

    if (!sheep)
        l_bank[1] ^= r_bank[1] ^= l_bank[1] ^= r_bank[1];

    if (!cabbage)
        l_bank[2] ^= r_bank[2] ^= l_bank[2] ^= r_bank[2];

    if (!farmer)
        l_bank[3] ^= r_bank[3] ^= l_bank[3] ^= r_bank[3];

    printf("%s || %s\n", l_bank, r_bank);
}

// Limited by memoization
int DFS(int wolf, int sheep, int cabbage, int farmer)
{
    if (mem[wolf][sheep][cabbage][farmer])
        return 0;

    mem[wolf][sheep][cabbage][farmer] = 1;

    // Loss state
    if ((wolf && sheep && !farmer) || (!wolf && !sheep && farmer) ||
        (sheep && cabbage && !farmer) || (!sheep && !cabbage && farmer))
        return 0;

	int depth = 1;
	
    PrintState(wolf, sheep, cabbage, farmer);

    // Win state
    if (!wolf && sheep && cabbage && farmer)
        return 1;

    depth += DFS(wolf ^ 1, sheep, cabbage, farmer ^ 1);
    depth += DFS(wolf, sheep ^ 1, cabbage, farmer ^ 1);
    depth += DFS(wolf, sheep, cabbage ^ 1, farmer ^ 1);
    depth += DFS(wolf, sheep, cabbage, farmer ^ 1);

    return depth;
}

// Limited by depth
int IDDFS(int wolf, int sheep, int cabbage, int farmer, int depth)
{
    // Limit breach
    if (depth < 0)
        return 0;

    // Loss state
    if ((wolf && sheep && !farmer) || (!wolf && !sheep && farmer) ||
        (sheep && cabbage && !farmer) || (!sheep && !cabbage && farmer))
        return 0;

    PrintState(wolf, sheep, cabbage, farmer);

    // Win state
    if (!wolf && !sheep && !cabbage && !farmer)
    {
        //PrintState(wolf, sheep, cabbage, farmer);
        return 1;
    }

    if (IDDFS(wolf ^ 1, sheep, cabbage, farmer ^ 1, depth - 1) || IDDFS(wolf, sheep ^ 1, cabbage, farmer ^ 1, depth - 1) ||
        IDDFS(wolf, sheep, cabbage ^ 1, farmer ^ 1, depth - 1) || IDDFS(wolf, sheep, cabbage, farmer ^ 1, depth - 1))
    {
        //PrintState(wolf, sheep, cabbage, farmer);
        return 1;
    }

    return 0;
}

void PushBFS(int wolf, int sheep, int cabbage, int farmer)
{
    if (!mem2[wolf][sheep][cabbage][farmer])
    {
        push(wolf); push(sheep); push(cabbage); push(farmer);
        mem2[wolf][sheep][cabbage][farmer] = 1;
    }
}

void BFS(int wolf, int sheep, int cabbage, int farmer)
{
    push(wolf); push(sheep); push(cabbage); push(farmer);
    mem2[wolf][sheep][cabbage][farmer] = 1;

    while(start != end)
    {
        wolf = pop(); sheep = pop(); cabbage = pop(); farmer = pop();

        // Loss state
        if ((wolf && sheep && !farmer) || (!wolf && !sheep && farmer) ||
        (sheep && cabbage && !farmer) || (!sheep && !cabbage && farmer))
        {
            continue;
        }

        PrintState(wolf, sheep, cabbage, farmer);

        // Win state
        if (!wolf && !sheep && !cabbage && !farmer)
        {
            return;
        }

        PushBFS(wolf ^ 1, sheep, cabbage, farmer ^ 1);
        PushBFS(wolf, sheep ^ 1, cabbage, farmer ^ 1);
        PushBFS(wolf, sheep, cabbage ^ 1, farmer ^ 1);
        PushBFS(wolf, sheep, cabbage, farmer ^ 1);
    }
}

int main()
{
    puts("DFS");
    printf("DFS: %d steps.\n", DFS(1, 1, 1, 1));

    puts("\nIDDFS");
    int depth, gotovo = 0;
    for(depth = 0; !gotovo; depth++)
    {
        printf("\nDepth : %d\n", depth);
        gotovo = IDDFS(1, 1, 1, 1, depth);
    }
    printf("IDDFS (shortest route): %d steps.\n", --depth);

    puts("\nBFS");
    BFS(1, 1, 1, 1);

    return 0;
}
