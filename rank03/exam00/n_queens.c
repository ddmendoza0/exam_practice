#include <stdio.h>
#include <stdlib.h>


int	is_valid(int *board, int row, int col)
{
	for (int i = 0; i < col; i++)
	{
		if (board[i] == row)
			return (0);
		if (col - i == board[i] - row || col - i == row - board[i])
			return (0);
	}
	return (1);
}

void	print_board(int *board, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (i != 0)
			printf(" ");
		printf("%i", board[i]);
	}
	printf("\n");
}

void	recursiva(int *board, int n, int col)
{
	if (col == n)
	{
		print_board(board, n);
		return ;
	}

	for (int row = 0; row < n; row++)
	{
		if (is_valid(board, row, col))
		{
			board[col] = row;
			recursiva(board, n, col + 1);
		}
	}
}


int	main(int argc, char **argv)
{
	if (argc != 2 || !argv[1])
		return (1);
	int	n = atoi(argv[1]);

	int	*board = malloc(sizeof(int) * n);
	if (!board)
		return (1);

	recursiva(board, n, 0);

	free(board);
	return (0);
}
