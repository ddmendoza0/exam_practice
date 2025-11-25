#include <stdlib.h>
#include <stdio.h>

void	print_subset(int *sum, int size_s)
{
	//impirmimos con los espacios donde toca
	for (int i = 0; i < size_s; i++)
	{
		if (i > 0)
			printf(" ");
		printf("%i", sum[i]);
	}
	printf("\n");
}

int	is_solution(int target, int *sum, int size_s)
{	//la suma de lo que hay en el array es igual al taget?
	int	total = 0;
	for (int i = 0; i < size_s; i++)
		total += sum[i];
	if (total != target)
		return (0);
	return (1);
}

void	recursiva(int *nums, int size_n, int target, int index, int *sum, int size_s)
{
	if (index == size_n) //llegamos al final
	{
		if (is_solution(target, sum, size_s) && size_s != 0)//si es solution y hay nums en la suma
			print_subset(sum, size_s);//imprimimos
		return ;
	}

	//no anadimos el numero al set de suma
	recursiva(nums, size_n, target, index + 1, sum, size_s);
	//anadimos el numero al set de suma
	sum[size_s] = nums[index];
	recursiva(nums, size_n, target, index + 1, sum, size_s + 1);
}	

int	main(int argc, char **argv)
{
	if (argc < 3) //verificación inicial
		return (1);
	int	target = atoi(argv[1]); //asignamos el target
	int	n_nums = argc - 2; //tamano del array de ints
	int	*nums = (int *)malloc(n_nums * sizeof(int)); //asignamos mem para el array de ints
	if (!nums)
		return (1);
	for (int i = 0; i < n_nums; i++) //bucle para recoger los nums entrantes
		nums[i] = atoi(argv[i + 2]);
	int	*sum = (int *)calloc(n_nums * sizeof(int)); //asignamos mem para los elementos sumados
	if (!sum)
	{
		free(nums);
		return (1);
	}
	recursiva(nums, n_nums, target, 0, sum, 0); //llamada a la f() recursiva
	free(nums);
	free(sum);
	return (0);
}
