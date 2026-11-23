#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct game {
    int wi;
    int he;
    int it;
    char **gr;
};

void free_grid(char **gr, int n)
{
    for (int i = 0; i < n; i++)
        free(gr[i]);
    free(gr);
}

int count_vecinos( struct game *g, int row, int col)
{
    int res = 0;

    for ( int dr = -1; dr <= 1; dr++ )
    {
        for ( int dc = -1; dc <= 1; dc++ )
        {
            if ( dr == 0 && dc == 0 )
                continue;
            if (row + dr >= g->he || row + dr < 0 || col + dc >= g->wi || col + dc < 0)
                continue;
            if ( g->gr[row+dr][col+dc] == 'O' )
                res++;
        }
    }

    return res;
}

int main (int argc, char **argv)
{
    if (argc != 4)
        return 1;

    // extraction
    struct game g;
    g.wi = atoi(argv[1]);
    g.he = atoi(argv[2]);
    g.it = atoi(argv[3]);

    // allocation
    g.gr = malloc(g.he * sizeof(char *));
    if (!g.gr)
        return 1;
    for (int i = 0; i < g.he; i++)
    {
        g.gr[i] = malloc(g.wi * sizeof(char));
        if (!g.gr[i])
        {
            free_grid(g.gr, i); 
            return 1;
        }
    }
    for (int i = 0; i < g.he; i++)
    {
        for (int j = 0; j < g.wi; j++)
            g.gr[i][j] = ' ';
    }

    //pencil stdin
    int row = 0;
    int col = 0;
    int drw = 0;

    char c;
    while (read(0, &c, 1) == 1)
    {
        if ( c == 'w' && row != 0 )
            row--;
        else if ( c == 's' && row != g.he - 1 )
            row ++;
        else if ( c == 'a' && col != 0 )
            col--;
        else if ( c == 'd' && col != g.wi - 1 )
            col++;
        else if ( c == 'x' )
            drw = !drw;

        if ( drw )
            g.gr[row][col] = 'O';
    }

    // iterations
    char **grid;
    grid = malloc(g.he * sizeof(char *));
    if (!grid)
    {
        free_grid(g.gr, g.he); 
        return 1;
    }
    for (int i = 0; i < g.he; i++)
    {
        grid[i] = malloc(g.wi * sizeof(char));
        if (!grid[i])
        {    
            free_grid(grid, i);
            free_grid(g.gr, g.he);
            return 1;
        }
    }
    for ( int b = 0; b < g.it; b++ )
    {
        for (int i = 0; i < g.he; i++)
        {
            for (int j = 0; j < g.wi; j++)
            {
                int n = count_vecinos(&g, i, j);
                if ( g.gr[i][j] == 'O' && (n == 2 || n == 3 ))
                    grid[i][j] = 'O';
                else if ( g.gr[i][j] == ' ' && n == 3 )
                    grid[i][j] = 'O';
                else
                    grid[i][j] = ' ';
            }
        }

        for (int i = 0; i < g.he; i++)
        {
            for (int j = 0; j < g.wi; j++)
                g.gr[i][j] = grid[i][j];
        }
    }
    free_grid(grid, g.he);

    // print
    for (int i = 0; i < g.he; i++)
    {
        for (int j = 0; j < g.wi; j++)
            putchar(g.gr[i][j]);
        putchar('\n');
    }

    // cleanup
    free_grid(g.gr, g.he);

    return 0;
}