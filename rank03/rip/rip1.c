#include <stdio.h>

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
			close++;
			if (close > open)
				return (0);
		}
	}
	if (open != close)
		return (0);
	if (open == 0)
		return (0);
	return (1);
}

void	recursiva(char *rip, int index, int rem, int max_rem)
{
	char	temp;
	
	if (rem == max_rem)
	{
		if (is_solution(rip))
			puts(rip);
		return ;
	}	
	if (!rip[index])
		return ;

	recursiva(rip, index + 1, rem, max_rem);

	temp = rip[index];
	rip[index] = ' ';
	recursiva(rip, index + 1, rem + 1, max_rem);
	rip[index] = temp;
}

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
			if (open > 0)
				open--;
			else
				close++;
		}
	}
	return (close + open);
}

int	is_valid_input(char *input)
{
	for(int i = 0; input[i]; i++)
	{
		if (input[i] != '(' && input[i] != ')')
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	if(!is_valid_input(argv[1]))
		return (1);
	
	recursiva(argv[1], 0, 0, min_removal(argv[1]));
	return (0);
}
