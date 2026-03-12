#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int	pos = 0;
char	*input;

int	expression();

int	factor()
{
	char	c = input[pos];

	if (c == '(')
	{
		pos++;
		int	res = expression();
		if (input[pos] != ')')
		{
			printf("Unexpected token '%c'\n", input[pos]);
			exit(1);
		}
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
	while (input[pos] == '*')
	{
		pos++;
		res *= factor();
	}
	return (res);

}

int	expression()
{
	int	res = term();

	while (input[pos] == '+')
	{
		pos++;
		res += term();
	}
	return (res);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	input = argv[1];
	int	res = expression();
	if (input[pos])
	{
		printf("Unexpected token '%c'\n", input[pos]);
		return (1);
	}
	printf("%i\n", res);
	return (0);
}
