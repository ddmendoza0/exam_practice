#include <stdio.h>


int	is_valid_input(char *src)
{
	int	i = 0;

	while(src[i])
	{
		if(src[i] != '(' && src[i] != ')')
			return (0);
		i++;
	}
	return (1);
}

int	is_balanced(char *rip)
{
	int	i = 0;
	int	rc = 0;
	int	lc = 0;

	while(rip[i])
	{
		if (rip[i] == '(')
			lc++;
		if(rip[i] == ')')
		{
		   	rc++;
			if (lc < rc)
				return (0);	
		}
		i++;
	}
	if (lc != rc)
		return (0);
	if (rc == 0)
		return (0);
	return (1);
}

int	min_removals(char *rip)
{
	int	i = 0;
	int	lc = 0;
	int	rc = 0;
	
	while(rip[i])
	{
		if (rip[i] == '(')
			lc++;
		else if (rip[i] == ')')
		{
			if (lc > 0)
				lc--;
			else
				rc++;
		}
		i++;
	}
	return (rc + lc);
}

void	recursiva(char *rip, int index, int removed, int max_remove)
{
	if (removed == max_remove)
	{
		if (is_balanced(rip))
			puts(rip);
		return ;
	}
	if(!rip[index])
		return ;
	
	char temp = rip[index];
	rip[index] = ' ';
	recursiva(rip, index + 1, removed + 1, max_remove);
	rip[index] = temp;
	
	recursiva(rip, index + 1, removed, max_remove);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	if (!is_valid_input(argv[1]))
		return(1);
	//int	min_removal = min_removals(argv[1]);
	//if (mion_rem == 0 && is_balanced(argv[1]))
	recursiva(argv[1], 0, 0, min_removals(argv[1]));
	return (0);
}
