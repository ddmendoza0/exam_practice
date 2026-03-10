

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int	picoshell(char	**cmds[])
{
	int	fds[2];
	pid_t	pid;
	int	pre = -1;

	for (int i = 0; cmds[i]; i++)
	{
		int	isl = !cmds[i +  1];
		if (!isl)
		{
			if (pipe(fds) == -1)
			{
				if (pre != -1)
					close(pre);
				return (1);
			}
		}
		pid = fork(); //ERROR - SIEMPRE HACE FORK
		if (pid == -1)
		{
			if(pre != 1)
				close(pre);
			close(fds[0]);
			close(fds[1]);
			return (1);
		}
		
		if (pid == 0)
		{
			if (pre != -1)
				dup2(pre, STDIN_FILENO);
			if (!isl)
				dup2(fds[1], STDOUT_FILENO);
			close(fds[1]);//close de los dos
			close(fds[0]);
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}

		//faltaba codigo padre
		if (pre != -1)
			close(pre);
		if (!isl)
		{
			close(fds[1]);
			pre = fds[0];
		}
	}
	while (wait(NULL) > 0)
		;
	return (0);
}
