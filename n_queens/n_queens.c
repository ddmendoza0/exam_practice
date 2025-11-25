#include <stdlib.h>
#include <stdio.h>

//funcion de validacion si podemos poner reina
int	is_valid(int fila, int columna, int *board)
{
	for (int i = 0; i < columna; i++) //hasta columna actual
	{
		if (board[i] == fila) //si es misma fila que ya hay en board
			return (0);
		if (columna - i == fila - board[i] || columna - i == board[i] - fila) //si es diagonal
			return (0);
	}
	return (1);

}

//imprimir la solucion
//puede que haya que craftear una funcion mas detallada
//depende del enunciado
void	print_solution(int *board, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (i > 0)
			printf(" ");
		printf("%i", board[i]);
	}
	printf("\n");

}

//funcion de recusividad
void	recursiva(int *board, int n, int columna)
{
	if (columna == n)//si hemos llegado al final
	{
		print_solution(board, n);
		return ;
	}

	for (int fila = 0; fila < n; fila++) //iteramos sobre la fila
	{
		if (is_valid(fila, columna, board)) //comprobamos si podemos poner reina en fila, columna
		{
			board[columna] = fila;	//anadimos la reina
			recursiva(board, n, columna + 1); //llamamos a recursiva con la siguiente columna
		}
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	if (!argv[1])
		return (1);
	int	n = atoi(argv[1]); //define board y reinas a colocar
	int	*board = malloc(sizeof(int) * n); //alojamos memoria para n elementos
	if (!board)
		return (1);
	
	//llamada a la funcion recursiva	
	recursiva(board, n, 0);

	free(board);
	return (0);
}
