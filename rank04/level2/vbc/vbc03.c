

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int	pos = 0;
char	*inp;

int	expression();

int	factor()
{
	char	c = inp[pos];

	if (c == '(')
	{
		pos++;
		int	res = expression();
		if (inp[pos] != ')')
			printf("Unexpected token '%c'\n", inp[pos]);
		pos++;
		return (res);
	}
	else if (isdigit(c))
	{
		pos++;
		return (c - '0');
	}
	
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input\n");
	exit(1);
}

int	term()
{
	int	res = factor();

	while (inp[pos] == '*')
	{
		pos++;
		res *= factor();
	}
	return (res);
}

int	expression()
{
	int	res = term();

	while (inp[pos] == '+')
	{
		pos++;
		res += term();
	}
	return (res);
}

int	main(int argc, char **argv)
{
	int	res;

	if (argc != 2)
		return (1);
	inp = argv[1];
	res = expression();
	if (inp[pos])
	{
		printf("Unexpected token '%c'\n", inp[pos]);
		exit(1);
	}
	printf("%i\n", res);
	return (0);
}
