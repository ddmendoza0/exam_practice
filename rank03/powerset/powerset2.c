#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void	print_solution(int *sum, int s_sum)
{
	for(int i = 0; i < s_sum; i++)
	{
		if (i != 0)
			printf(" ");
		printf("%i", sum[i]);
	}
	printf("\n");
}

int	is_solution(int *sum, int s_sum, int target)
{
	int	total = 0;
	for(int i = 0; i < s_sum; i++)
		total += sum[i];
	
	if (total != target)
		return (0);
	return (1);

}

void	recursiva(int *nums, int s_nums, int *sum, int s_sum, int index, int target)
{
	if (index == s_nums)
	{
		if (is_solution(sum, s_sum, target) && size_s != 0)//numeros de la suma
			print_solution(sum, s_sum);
		return ;
	}

	recursiva(nums, s_nums, sum, s_sum, index + 1, target);

	sum[s_sum] = nums[index];
	recursiva(nums, s_nums, sum, s_sum + 1, index + 1, target);
}


int	main(int argc, char **argv)
{
	if (argc < 3)
		return (1);

	int	s_nums = argc - 2;
	int	target = atoi(argv[1]);
	int	*nums = malloc(sizeof(int) * s_nums);
	if (!nums)
		return (1);
	for (int i = 0; i < s_nums; i++)
		nums[i] = atoi(argv[i + 2]);
	
	int	*sum = calloc(sizeof(int), s_nums);
	if (!sum)
	{
		free(nums);
		return (1);
	}
	
	recursiva(nums, s_nums, sum, 0, 0, target);

	free(nums);
	free(sum);
	return (0);
}
