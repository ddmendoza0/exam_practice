#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

struct game {
    int     wi;
    int     hi;
    int     it;
    char    **gr;
};

void free_grid(char** grid, int n)
{
    for ( int i = 0; i < n; i++ )
        free(grid[i]);
    free(grid);
}

int count_veci(struct game *g, int row, int col)
{
    int res = 0;

    for ( int drow = -1; drow <= 1; drow++ ) //fallo drow < 1
    {
        for ( int dcol = -1; dcol <= 1; dcol++) // fallo dcol < 1
        {
            if ( dcol == 0 && drow == 0 )
                continue;
            if ( (row + drow < 0) || (row + drow >= g->hi) || col + dcol < 0 || col + dcol >= g->wi )
                continue;
            if ( g->gr[row+drow][col+dcol] == 'O' ) //fallo [drow][dcol]
                res++;
        }
    }
    return res;
}

int main(int argc, char **argv)
{
    if (argc != 4)
        return 1;

    //allocation
    struct game g;
    g.wi = atoi(argv[1]);
    g.hi = atoi(argv[2]);
    g.it = atoi(argv[3]);

    g.gr = malloc(g.hi * sizeof(char *));
    if (!g.gr)
        return 1;
    for ( int i = 0; i < g.hi; i++ )
    {
        g.gr[i] = malloc(g.wi * sizeof(char));
        if (!g.gr[i])
        {
            free_grid(g.gr, i);
            return 1;
        }
    }

    for ( int i = 0; i < g.hi; i++ )
    {
        for ( int j = 0; j < g.wi; j++ )
            g.gr[i][j] = ' ';
    }

    //draw commands
    int col = 0;
    int row = 0;
    int drw = 0;

    char c;
    while ( read(0, &c, 1) == 1 )
    {
        if ( c == 'w' && row != 0 )
            row--;
        else if ( c == 's' && row != g.hi - 1 )
            row++;
        else if ( c == 'a' && col != 0 )
            col--;
        else if ( c == 'd' && col != g.wi - 1 ) 
            col++;
        else if ( c == 'x' )
            drw = !drw;

        if (drw)
            g.gr[row][col] = 'O';
    }


    // iterations run
    char **grid;
    grid = malloc(g.hi * sizeof(char *));
    if (!grid)
    {
        free_grid(g.gr, g.hi);
        return 1;
    }
    for ( int i = 0; i < g.hi; i++ )
    {
        grid[i] = malloc(g.wi * sizeof(char));
        if (!grid[i])
        {
            free_grid(g.gr, g.hi);
            free_grid(grid, i);
            return 1;
        }
    }

    for ( int n = 0; n < g.it; n++ )
    {
        for ( int i = 0; i < g.hi; i++ )
        {
            for (int j = 0; j < g.wi; j++) // fallo i++
            {
                int veci = count_veci(&g, i, j);

                if ( g.gr[i][j] == 'O' && (veci == 2 || veci == 3))
                    grid[i][j] = 'O';
                else if (g.gr[i][j] == ' ' && veci == 3 )
                    grid[i][j] = 'O';
                else
                    grid[i][j] = ' ';
            }
        }

        for ( int i = 0; i < g.hi; i++ )
        {
            for (int j = 0; j < g.wi; j++) // fallo i++
            {
                g.gr[i][j] = grid[i][j];   
            }
        }
    }

    free_grid(grid, g.hi);

    for ( int i = 0; i < g.hi; i++ )
    {
        for ( int j = 0; j < g.wi; j++ ) // fallo i++
        {
            //putchar('0' + count_veci(&g, i, j));
            putchar(g.gr[i][j]);
        }
        putchar('\n');
    }
    free_grid(g.gr, g.hi);

    return 0;
}