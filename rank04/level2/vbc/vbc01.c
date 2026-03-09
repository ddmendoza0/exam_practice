
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

//declaracion de globales
char	*input;
int	pos = 0;

//pre declaracion para el compiler
int	expression();

//la chicha
int	factor()
{
	char	c = input[pos];

	if (c == '(')//busca resolver cada parentesis con el suyo que cierra.
	{
		pos++;
		int result = expression();
		if (input[pos] != ')')
		{
			printf("Unexpected token '%c'\n", input[pos]);
			exit(1);
		}
		pos++;
		return (result);
	}
	else if (isdigit(c))//retorna el numero que detecte
	{
		pos++;
		return (c - '0');
	}
	else//si llega aqui es erroneo
	{
		if (!c)
			printf("Unexpected end of input\n");
		else
			printf("Unexpected token '%c'\n", c);
		exit(1);
	}
}

int	term()
{
	int	result = factor();
	while (input[pos] == '*')
	{
		pos++;
		result *= factor();
	}
	return (result);
}

int	expression()
{
	int	result = term();

	while (input[pos] == '+')
	{
		pos++;
		result += term();
	}
	return (result);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (1);
	input = argv[1];
	int	result = expression();
	if (input[pos])
	{
		printf("Unexpected token %c\n", input[pos]);
		exit(1);
	}
	printf("%d\n", result);
	return (0);
}




