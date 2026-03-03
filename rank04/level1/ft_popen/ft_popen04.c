
#include <unistd.h>
#include <stdlib.h>

int ft_popen(const char *file, char *const argv[], char type)
{
	pid_t	pid;
	int	pipefd[2];

	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);

	if (pipe(pipefd) == -1)
		return (-1);

	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}

	if (pid == 0)
	{
		if (type == 'r')
			dup2(pipefd[1], STDOUT_FILENO);
		else
			dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		execvp(file, argv);
		exit(1);
	}
	if (type == 'r')
	{
		close(pipefd[1]);
		return (pipefd[0]);
	}
	else 
	{
		close(pipefd[0]);
		return (pipefd[1]);
	}
}	
