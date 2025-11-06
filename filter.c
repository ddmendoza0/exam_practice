#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

// Función para buscar y reemplazar
void	ft_filter(char* buffer, char* pattern)
{
	int	i;
	int	j;
	int	len;
	int	k;

	i = 0;
	len = strlen(pattern);
	while (buffer[i])
	{
		j = 0;
		while (pattern[j] && buffer[i + j] == pattern[j])
			j++;
		if (j == len)
		{
			k = 0;
			while (k < len)
			{
				write(1, "*", 1);
				k++;
			}
			i += len;
		}
		else
		{
			write(1, &buffer[i], 1);
			i++;
		}
	}
}

// Función para leer todo stdin
char* read_all(void)
{
	char	temp[BUFFER_SIZE];
	char* result;
	char* new_result;
	int		total;
	int		bytes;

	result = NULL;
	total = 0;
	while ((bytes = read(0, temp, BUFFER_SIZE)) > 0)
	{
		new_result = malloc(total + bytes + 1);
		if (!new_result)
		{
			perror("Error");
			free(result);
			return (NULL);
		}
		if (result)
		{
			memcpy(new_result, result, total);
			free(result);
		}
		memcpy(new_result + total, temp, bytes);
		total += bytes;
		new_result[total] = '\0';
		result = new_result;
	}
	if (bytes < 0)
	{
		perror("Error");
		free(result);
		return (NULL);
	}
	return (result);
}

int	main(int argc, char** argv)
{
	char* buffer;

	if (argc != 2 || !argv[1] || argv[1][0] == '\0')
		return (1);

	buffer = read_all();
	if (!buffer)
		return (1); // Cambiado: si hay error, return 1

	ft_filter(buffer, argv[1]);

	free(buffer);
	return (0);
}