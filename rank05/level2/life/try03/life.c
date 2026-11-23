#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

struct game {
    int     w;
    int     h;
    int     i;
    char**  g;
};

void    free_grid(char **grid, int n)
{
    for ( int i = 0; i < n; i++ )
        free(grid[i]);
    free(grid);
}

int count_vecinos(struct game *g, int row, int col )
{
    int res = 0;

    for ( int i = -1; i <= 1; i++ )
    {
        for ( int j = -1; j <= 1; j++ )
        {
            if (i == 0 && j == 0 ) // no es col y row 
                continue;
            if ( row + i >= g->h || row + i < 0 || col + j >= g->w || col + j < 0 )
                continue;
            if ( g->g[row+i][col+j] == 'O' )
                res++;
        }
    }
    return res;
}

int main( int argc, char **argv)
{
    if ( argc != 4 )
        return 1;

    //allocation
    struct game g;
    g.w = atoi(argv[1]);
    g.h = atoi(argv[2]);
    g.i = atoi(argv[3]);

    g.g = malloc(g.h * sizeof(char *));
    if (!g.g)
        return 1;
    for ( int i = 0; i < g.h; i++ )
    {
        g.g[i] = malloc(g.w * sizeof(char));
        if (!g.g[i])
        {
            free_grid(g.g, i);
            return 1;
        }
        for ( int j = 0; j < g.w; j++ )
            g.g[i][j] = ' ';
    }

    //commands admission
    int row = 0;
    int col = 0;
    int drw = 0;

    char c;
    while ( read(0, &c, 1) == 1 )
    {
        if ( c == 'w' && row != 0 )
            row--;
        else if ( c == 's' && row != g.h - 1 )
            row++;
        else if ( c == 'a' && col != 0 )
            col--;
        else if ( c == 'd' && col != g.w - 1 )
            col++;
        else if ( c == 'x' )
            drw = !drw;

        if ( drw )
            g.g[row][col] = 'O';
    }

    // iterations
    char **grid;
    grid = malloc(g.h * sizeof(char *));
    if (!grid)
    {
        free_grid(g.g, g.h);
        return 1;
    }
    for ( int i = 0; i < g.h; i++ )
    {
        grid[i] = malloc(g.w * sizeof(char));
        if (!grid[i])
        {
            free_grid(grid, i);
            free_grid(g.g, g.h);
            return 1;
        }
    }

    for ( int it = 0; it < g.i; it++ )
    {
        for ( int i = 0; i < g.h; i++ )
        {
            for ( int j = 0; j < g.w; j++)
            {
                int n = count_vecinos(&g, i, j);
                if ( g.g[i][j] == 'O' && ( n == 2 || n == 3))
                    grid[i][j] = 'O';
                else if ( g.g[i][j] == ' ' && n == 3 )
                    grid[i][j] = 'O';
                else
                    grid[i][j] = ' ';
            }
        }

        for ( int i = 0; i < g.h; i++ )
        {
            for ( int j = 0; j < g.w; j++)
                g.g[i][j] = grid[i][j];
        }
    }
    free_grid(grid, g.h);



    //imprimir y cleanup
    for ( int i = 0; i < g.h; i++ )
    {
        for ( int j = 0; j < g.w; j++ )
        {
            //putchar('0' + count_vecinos(&g, i, j)); // sin el '0' + por lo que salian caracteres raros
            putchar(g.g[i][j]);
        }
        putchar('\n');
    }

    free_grid(g.g, g.h);

    return 0;
}