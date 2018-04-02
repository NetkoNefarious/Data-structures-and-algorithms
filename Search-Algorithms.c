#include <stdio.h>
#define MAXSIZE 10000

// Slagalica 2x3
int mem[6][6][6][6][6][6] = {0}; // Svi elementi se inicijaliziraju na 0.
int queue[MAXSIZE], pocetak, kraj;

void push(int x)
{
    queue[kraj++] = x;
    kraj %= MAXSIZE;
}

int pop()
{
    int x = queue[pocetak++];
    pocetak %= MAXSIZE;
    return x;
}

int DFS(int a, int b, int c, int d, int e, int f)
{
    if (mem[a-1][b-1][c-1][d-1][e-1][f-1])
        return 0;

    printf("\n%d %d %d\n%d %d %d\n", a, b, c, d, e, f);

    mem[a-1][b-1][c-1][d-1][e-1][f-1] = 1;

    if (a == 1 && b == 2 && c == 3 && d == 4 && e == 5 && f == 6)
        return 1;

    if (DFS(b, a, c, d, e, f) || DFS(a, c, b, d, e, f) || DFS(d, b, c, a, e, f) || DFS(a, e, c, d, b, f) ||
        DFS(a, b, f, d, e, c) || DFS(a, b, c, e, d, f) || DFS(a, b, c, d, f, e))
        return 1;

    return 0;
}

int IDDFS(int a, int b, int c, int d, int e, int f, int dubina)
{
    if (dubina < 0)
        return 0;

    if (a == 1 && b == 2 && c == 3 && d == 4 && e == 5 && f == 6)
    {
        puts("\n1 2 3\n4 5 6");
        return 1;
    }

    if (IDDFS(b, a, c, d, e, f, dubina - 1) || IDDFS(a, c, b, d, e, f, dubina - 1) || IDDFS(d, b, c, a, e, f, dubina - 1) ||
        IDDFS(a, e, c, d, b, f, dubina - 1) || IDDFS(a, b, f, d, e, c, dubina - 1) || IDDFS(a, b, c, e, d, f, dubina - 1) ||
        IDDFS(a, b, c, d, f, e, dubina - 1))
    {
        printf("\n%d %d %d\n%d %d %d\n", a, b, c, d, e, f);
        return 1;
    }

    return 0;
}

void push_BFS(int a, int b, int c, int d, int e, int f) // Pomocna funkcija
{
    if (!mem[a-1][b-1][c-1][d-1][e-1][f-1])
    {
        push(a); push(b); push(c); push(d); push(e); push(f);
        mem[a-1][b-1][c-1][d-1][e-1][f-1] = 1;
    }
}

int BFS(int a, int b, int c, int d, int e, int f)
{
    int razina = 1, i = 7;
    push(a); push(b); push(c); push(d); push(e); push(f);
    mem[a-1][b-1][c-1][d-1][e-1][f-1] = 1;

    while (pocetak != kraj)
    {
        a = pop(); b = pop(); c = pop(); d = pop(); e = pop(); f = pop();

        printf("\n%d %d %d\n%d %d %d\n", a, b, c, d, e, f);

        if (a == 1 && b == 2 && c == 3 && d == 4 && e == 5 && f == 6)
            return razina;

        push_BFS(a, c, b, d, e, f);
        push_BFS(b, a, c, d, e, f);
        push_BFS(a, b, c, e, d, f);
        push_BFS(a, b, c, d, f, e);
        push_BFS(d, b, c, a, e, f);
        push_BFS(a, e, c, d, b, f);
        push_BFS(a, b, f, d, e, c);

        if (i++ == 7)
        {
            razina++;
            i = 0;
        }
    }

    return -1;
}

int main()
{
    int a, b, c, d, e, f;
    fputs("Unesite zeljenu slagalicu: ", stdout);
    scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
/*
    fputs("DFS:", stdout);
    DFS(a, b, c, d, e, f);
    int mem[6][6][6][6][6][6] = {0};

    fputs("\nIDDFS:", stdout);
    int dubina;
    for (dubina = 0; !IDDFS(a, b, c, d, e, f, dubina); dubina++)
        ;

    if (dubina % 20 == 1)
        puts("\nNasli smo rjesenje u jednom koraku.");
    else
        printf("\nNasli smo rjesenje u %d koraka.\n", dubina);
*/
    fputs("\nBFS:", stdout);
    pocetak = kraj = 0;

    printf("\nRjesenje je slozeno u %d. razini.", BFS(a, b, c, d, e, f));

    return 0;
}
