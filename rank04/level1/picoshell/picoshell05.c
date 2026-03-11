

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int	picoshell(char **cmds[])
{
	int	fds[2];
	pid_t	pid;
	int	pre = -1;

	for (int i = 0; cmds[i]; i++)
	{
		int	isl = !cmds[i + 1];
		if (!isl)
		{
			if (pipe(fds) == -1)
			{
				if (pre != -1)
					close(pre);
				return (1);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			if (pre != -1)
				close(pre);
			if (!isl)
			{
				close(fds[0]);
				close(fds[1]);
			}
			return (1);
		}

		if (pid == 0)
		{
			if (pre != -1)
			{
				dup2(pre, STDIN_FILENO);
				close(pre);
			}
			if (!isl)
			{
				dup2(fds[1], STDOUT_FILENO);
				close(fds[0]);
				close(fds[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}

		if (pre != -1)// fallo aqui.
		{
			close(pre);//acordarse de cerrar lo mismo que arriba
		}
		if (!isl)
		{
			close(fds[1]);//empalmar si no es el ultimo
			pre = fds[0];//siguiendo la sequencia de arrba de no islast
		}
	}
	while (wait(NULL) > 0)
		;
	return (0);
}
