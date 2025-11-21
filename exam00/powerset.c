#include <stdio.h>
#include <stdlib.h>

void	print_solution(int *sum, int n_sum)
{
	for (int i = 0; i < n_sum; i++)
	{
		if (i != 0)
			printf(" ");
		printf("%i", sum[i]);
	}
	printf("\n");
}

int	is_solution(int *sum, int n_sum, int target)
{
	int result = 0;

	for (int i = 0; i < n_sum; i++)
		result += sum[i];
	if (result != target)
		return (0);
	return (1);
}


void	recursiva(int *set, int n_set, int *sum, int n_sum, int target, int index)
{
	if (index == n_set)
	{
		if (is_solution(sum, n_sum, target) && n_sum != 0)
			print_solution(sum, n_sum);
		return ;
	}

	recursiva(set, n_set, sum, n_sum, target, index + 1);

	sum[n_sum] = set[index];
	recursiva(set, n_set, sum, n_sum + 1, target, index + 1);
}

int	main(int argc, char **argv)
{
	if (argc < 3)
		return (1);

	int	target = atoi(argv[1]);

	int	n_num = argc - 2;

	int	*set = malloc(sizeof(int) * n_num);
	if (!set)
		return (1);

	for (int i = 0; i < n_num; i++)
		set[i] = atoi(argv[i + 2]);

	int	*sum = calloc(n_num, sizeof(int));
	if (!sum)
	{
		free(set);
		return (1);
	}
	recursiva(set, n_num, sum, 0, target, 0);

	free(sum);
	free(set);
	return (0);
}
