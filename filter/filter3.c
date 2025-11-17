#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif


void	filter(char *aguja, char *pajar)
{
	size_t	i = 0;
	size_t	j;

	while (pajar[i])
	{
		j = 0;
		while (aguja[j] == pajar[i+j] && aguja[j])
			j++;
		if (j == strlen(aguja))
		{
			while (j > 0)
			{
				write(1, "*", 1);
				j--;
			}
			i += strlen(aguja);
		}
		else
			write(1, &pajar[i++], 1);
	}
}

char	*read_all(void)
{
	int	r_bytes = 0;
	int	t_bytes = 0;
	char	*temp;
	char	*result = NULL;
	char	*buffer = malloc(BUFFER_SIZE);
	if (!buffer)
	{
		perror("Error");
		return (NULL);
	}
	while ((r_bytes = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		temp = realloc(result, t_bytes + r_bytes + 1);
		if (!temp)
		{
			free(buffer);
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
	if(argc != 2)
		return (1);
	if (argv[1][0] == '\0')
		return (1);
	char	*pajar = read_all();
	if (!pajar)
		return (1);
	filter(argv[1], pajar);
	return (0);
}
