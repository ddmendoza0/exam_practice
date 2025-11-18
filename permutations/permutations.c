#include <stdio.h>
#include <stdlib.h>


void	recursiva(char *str, char *permutation, int *used, int len, int index)
{
	if (index == len) //si llegamos al final imprimimos
	{
		permutation[index] = '\0';
		puts(permutation);
		return ;
	}
	
	for (int i = 0; i < len; i++) //iteramos desde el inicio siempre
	{
		if (!used[i]) //si el caracter no esta usado generamos permutaciones
		{
			used[i] = 1; //arriba flag
			permutation[index] = str[i]; //añadimos el caracter en la nueva permutacion
			recursiva(str, permutation, used, len, index + 1); //recurrir
			used[i] = 0; //abajo flag
		}
	}

}

//ordenacion previa
void	sort_str(char	*str)
{
	int	i = 0;
	char	temp;

	while (str[i])
	{
		if(str[i + 1] == '\0')
			break;
		if (str[i] > str[i + 1])
		{
			temp = str[i];
			str[i] = str[i + 1];
			str[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}


int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	if (!argv[1])
		return (1);
	
	int len = 0; //calculamos len del string
	while(argv[1][len])
		len++;
	
	//alojamos memoria para las permutaciones
	char	*permutation = malloc(sizeof(char) * (len + 1));
	if (!permutation)
		return (1);
	//alojamos memoria a 0 para el array de bloqueos
	int	*used = calloc(sizeof(int), len);
	if (!used)
	{
		free(permutation);
		return (1);
	}
	
	//ordenamos previo
	sort_str(argv[1]);
	
	//primera llamada a recursion
	recursiva(argv[1], permutation, used, len, 0);
	
	free(used);
	free(permutation);
	return (0);
}
