#include <stdio.h>
#include <stdlib.h>

void	sort_input(char *input)
{
	int	i = 0;
	char	temp;

	while (input[i + 1])
	{
		if (input[i] > input[i + 1])
		{
			temp = input[i];
			input[i] = input[i + 1];
			input[i + 1] = temp;			
			i = 0;
		}
		else
			i++;
	}
}

void	recursiva(char *src, char *permuta, int	*used, int len, int index)
{
	if (index == len)
	{
		permuta[index] = '\0';
		puts(permuta);
		return ;
	}

	for (int i = 0; i < len; i++)
	{
		if (!used[i])
		{
			used[i] = 1;
			permuta[index] = src[i]; //se monta la permuta en la posicion index con src en i
			recursiva(src, permuta, used, len, index + 1);
			used[i] = 0;
		}
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2 || !argv[1])
		return (1);

	sort_input(argv[1]);

	int	s_len = 0;
	while (argv[1][s_len])
		s_len++;

	int	*used = malloc(sizeof(int) * s_len);
	if (!used)
		return (1);
	
	char	*permutation = malloc(s_len);
	if (!permutation)
	{
		free(used);
		return (1);
	}
	recursiva(argv[1], permutation ,used, s_len, 0);

	free(used);
	return (0);
}
