#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	filter(char *pajar, char *aguja)
{
	size_t	i, j;

	i = 0;
	while(pajar[i])
	{
		j = 0;
		while(pajar[j + i] == aguja[j] && aguja[j])
			j++;

		if(strlen(aguja) == j)
		{
			while(j > 0)
			{
				write(1,"*",1);
				j--;
			}
			i += strlen(aguja);
		}
		else
		{
			write(1, &pajar[i], 1);
			i++;
		}
	}
	return (1);
}


char	*read_all(void)
{
	char	*buffer;
	char	*result = NULL;
	char	*temp;
	int	t_bytes = 0;
	int	r_bytes = 0;

	buffer = (char *)malloc(BUFFER_SIZE);
	if(!buffer)
	{
		perror("Error");
		return (NULL);
	}
	while((r_bytes = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		temp = realloc(result, t_bytes + r_bytes + 1);
		if (!temp)
		{
			free(buffer);
			free(result);
			perror("Error");
			return (NULL);
		}
		result = temp;
		memmove(result + t_bytes, buffer, r_bytes);
		t_bytes += r_bytes;
		result[t_bytes] = '\0';
	}
	free(buffer);
	if(r_bytes < 0)
	{
		free(result);
		perror("Error");
		return (NULL);
	}
	return (result);
}


int	main(int argc, char *argv[])
{
	char	*pajar;

	if(argc != 2 || !argv[1] || argv[1][0] == '\0')
		return(1);
	if(!(pajar = read_all()))
		return (1);
	if(!filter(pajar, argv[1]))
	{
		free(pajar);
		perror("Error");
		return (1);
	}
	free(pajar);
	return (0);
}
