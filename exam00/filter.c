#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

void	filter(char *pajar, char *aguja)
{
	size_t	i = 0;
	size_t	j;

	while (pajar[i])
	{
		j = 0;
		while (aguja[j] == pajar[i + j] && pajar[i + j])
			j++;
		if (strlen(aguja) == j)
		{
			while (j-- > 0)
				write(1,"*",1);
			i += strlen(aguja);
		}
		else
		{
			write(1, &pajar[i], 1);
			i++;
		}
	}
}

char	*read_all(void)
{
	char	*buffer = malloc(BUFFER_SIZE);
	if (!buffer)
	{
		perror("Error");
		return (NULL);
	}
	char	*result = NULL;
	char	*temp;
	int	t_bytes = 0;
	int	r_bytes;

	while ((r_bytes = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		temp = realloc(result, t_bytes + r_bytes + 1);
		if (!temp)
		{
			free(result);//fallo liberar
			free(buffer);
			perror("Error");
			return (NULL);
		}
		result = temp;
		memmove(result + t_bytes, buffer, r_bytes);
		t_bytes += r_bytes;
		result[t_bytes] = '\0';
	}
	free(buffer);
	if (r_bytes < 0)
	{
		free(result);
		perror("Error");
		return (NULL);	
	}

	return (result);
}

int	main(int argc, char **argv)
{
	if (argc != 2 || !argv[1])
		return (1);

	char	*pajar = read_all();
	if (!pajar)
		return(1);

	filter(pajar, argv[1]);

	free(pajar);
	return (0);
}
