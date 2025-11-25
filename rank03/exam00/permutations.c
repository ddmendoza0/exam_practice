#include <stdlib.h>
#include <stdio.h>

void	super_sort(char *src)
{
	int	i = 0;
	char	temp;

	while (src[i] && src[i + 1])
	{
		if (src[i] > src[i + 1])
		{
			temp = src[i];
			src[i] = src[i + 1];
			src[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}


void	recursiva(char *src, char *permuta, int *used, int len, int index)
{
	if (index == len)
	{
		puts(permuta);
		return ;
	}

	for (int i = 0; i < len; i++)
	{
		if (!used[i])
		{
			used[i] = 1;
			permuta[index] = src[i];
			recursiva(src, permuta, used, len, index + 1);
			used[i] = 0;
		}
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2 || !argv[1])
		return (1);

	int len = 0;
	while (argv[1][len])
		len++;

	char	*permuta = malloc(len + 1);
	if (!permuta)
		return (1);

	int	*used = malloc(sizeof(int) * len);
	if (!used)
	{
		free(permuta);
		return (1);
	}
	for (int i = 0; i < len; i++)
		used[i] = 0;

	super_sort(argv[1]);
	
	recursiva(argv[1], permuta, used, len, 0);

	free(used);
	free(permuta);
	return (0);
}
