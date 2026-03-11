

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int	picoshell(char **cmds[])
{
	int	pre = -1;
	pid_t	pid;
	int	fds[2];

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
			close(fds[0]);
			close(fds[1]);
			return (1);
		}

		if (pid == 0)
		{
			if (pre != -1)
			{
				dup2(pre, STDIN_FILENO);
				close(pre); //fallo hay que cerrar el fd despues de duplicar.
			}
			if (!isl)
			{
				dup2(fds[1], STDOUT_FILENO);
				close(fds[0]);//fallo - close dentro del if porque el ultimo
				close(fds[1]);//no crea pipes, los fds estan vacios
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}

		if (pre != -1) //fallo en el padre
			close(pre);//if no pre cerrar pre
		if (!isl) //if no ultimo empalmar el pre.
		{
			close(fds[1]);
			pre = fds[0];
		}
	}
	while (wait(NULL) > 0)
		;
	return (0);
}
