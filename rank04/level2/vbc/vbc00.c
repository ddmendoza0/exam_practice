
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//globales para gestionar el input y la posicion dentro de el
char	*input;
int	pos = 0;

int	expression();

//aqui la chicha
//gestionamos los parentesisi y para cualquier operacion que haya dentro vuelve a empezar
int	factor()
{
	char	c = input[pos];//sacamos el caracter actual

	if (c == '(')//si es un parentesis buscaremos el final
	{
		pos++;
		int	res = expression();//llamamos para solucionar operaciones
		if (input[pos] != ')')//si no estamos en el parentesis que cierra error
		{
			printf("Unexpected token '%c'\n",input[pos]);
			exit(1);
		}
		pos++;
		return (res);
	}
	else if (isdigit(c))//si encontramos un numero lo devolvemos de char a int
	{
		pos++;
		return (c - '0');
	}
	else//aqui error. si hemos llegado aqui es un caracter no controlado
	{	//o es un string malformado, operacion que se acaba sin digito...
		if (!c) //si el caracter que llega es nulo
			printf("Unexpected end of input\n");
		else //si es cualquier cosa no contemplada
			printf("Unexpected token '%c\n", c);
		exit(1);
	}
}

//gestion de multiplicaciones
//lo mismo que con la anterior vamos hacia dentro solucionando las prioridades
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

//como lo ultimo que tenemos que gestionar son las sumas
//esta funcion envia la llamada hacia dentro hasta que solo queden numeros que sumar
int	expression()
{
	int	res = term();//llama a multiplicacion

	while(input[pos] == '+')//suma valores
	{
		pos++;
		res += term();//resuelve el siguiente espacio despues del +
	}
	return (res); //devuelve resultado final
}

//inicio del programa
int	main(int argc, char **argv)
{
	// comprovaciones previas
	if (argc != 2) // si tiene mas argumentos de los que toca return
		return (1);
	
	input = argv[1]; // asignamos el input
	
	//iniciamos el solver recursivo
	int	res = expression();

	if (input[pos])//si al salir del bucle no esta en la ultima posicion error
	{
		printf("Unexpected token '%c'\n", input[pos]);
		exit(1);
	}
	//impresion de resultado
	printf("%d\n", res);
	return (0);
}
