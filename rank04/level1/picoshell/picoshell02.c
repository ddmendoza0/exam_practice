

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int	picoshell(char **cmds[])
{
	int	fds[2];
	pid_t	pid;
	int	pre = -1;

	//bucle principal con durante cmds
	for (int i = 0; cmds[i]; i++)
	{
		int	isl = !cmds[i + 1];//bool para encontrar la ultima iteracion
		if (!isl)//creacion de pipes, el ultimo no necesita mas pipes
		{
			if(pipe(fds) == -1)
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
			if (pre != -1)//asignamos la entrada de datos a la instruccion anterior
			{
				dup2(pre, STDIN_FILENO);
				close(pre);
			}

			if(!isl)//asignamos la salida de datos al 1
			{
				dup2(fds[1], STDOUT_FILENO);
				close(fds[0]);
				close(fds[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}

		if (pre != -1)
			close(pre);
		if (!isl)//enviamos al siguiente bucle el fd libre para que se convierta en la salida de datos
		{
			close(fds[1]);
			pre = fds[0];
		}
	}
	while (wait(NULL) > 0)
		;
	return (0);
}
