#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


void print_solution(int *solution, int sol_size)
{
	for (int i = 0; i < sol_size; i++)
	{
		if (i > 0)
			printf(" ");
		printf("%d", solution[i]);
	}
	printf("\n");
}


void	solver(int *nums, int n, int target, int idx, int current_sum, int *solution, int sol_size)
{
	// comprobación de caso base
	// cuando lleags al final
	if (idx == n)
	{
		// si la suma es target y tenemos 1 numero min: imprime.
		if (current_sum == target && sol_size > 0)
			print_solution(solution, sol_size);
		return ;
	}
	
	//avanzar de numero
	solver(nums, n, target, idx + 1, current_sum, solution, sol_size);

	//anadimos el numero en este indice a la solucion
	solution[sol_size] = nums[idx];
	solver(nums, n, target, idx + 1, current_sum + nums[idx], solution, sol_size + 1);
}

int	main(int argc, char **argv)
{
	if (argc < 3)
		return (0);
	int	target = atoi(argv[1]);
	int	n = argc - 2;
	int	*nums = malloc(sizeof(int) * n);
	if(!nums)
		return (1);
	for (int i = 0; i < n; i++)
		nums[i] = atoi(argv[i + 2]);
	
	int	*solutions = malloc(sizeof(int) * n);
	if (!solutions)
	{
		free(nums);
		return (1);
	}

	solver(nums, n, target, 0, 0, solutions, 0);

	free(solutions);	
	free(nums);
	return (0);
}
