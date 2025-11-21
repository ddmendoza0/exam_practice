#include <stdio.h>



int	min_removal(char *rip)
{
	int	open = 0;
	int	close = 0;

	for (int i = 0; rip[i]; i++)
	{
		if (rip[i] == '(')
			open++;
		if (rip[i] == ')') 
		{
			if (open > 0) //comparacion con 0!!
				open--;
			else 
				close++;
		}
	}
	return (close + open);
}

int	is_solution(char *rip)
{
	int	open = 0;
	int	close = 0;

	for (int i = 0; rip[i]; i++)
	{
		if (rip[i] == '(')
			open++;
		if (rip[i] == ')')
		{
			if (open > close)
				open--;
			else
				return (0);
		}
	}
	if (open != 0)
		return (0);
	return (1);
}

void	recursiva(char *rip, int min_rem, int rem, int index)
{
	if (!rip[index] || min_rem == rem)
	{
		if (is_solution(rip))
			puts(rip);
		return ;
	}

	recursiva(rip, min_rem, rem, index + 1);

	char	temp;
	temp = rip[index];
	rip[index] = ' ';
	recursiva(rip, min_rem, rem + 1, index + 1);
	rip[index] = temp;
}

int	main(int argc, char **argv)
{
	if (argc != 2 || !argv[1])
		return (1);


	int	min_rem = min_removal(argv[1]);
	recursiva(argv[1], min_rem, 0, 0);

	return (0);
}
