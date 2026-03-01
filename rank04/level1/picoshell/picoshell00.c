
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


void	close_all(int *prev_read, int pipefd[2], int pipe_created)
{
	if (*prev_read != -1)
		close(*prev_read);
	if (pipe_created)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

int	picoshell(char **cmds[])
{
	//declaracion
	int	prev_read; //lectura del pipe anterior
	int	pipefd[2]; //pipe actual
	pid_t	pid;
	int	i;

	prev_read = -1; //el primer comando no tiene pipe anterior
	i = -1;
	while (cmds[++i])
	{
		int is_last = (cmds[i + 1] == NULL); //obtencion del bool es ultimo
		if (!is_last) //si no es el ultimo creamos pipes
		{
			if (pipe(pipefd) == -1)
			{
				close_all(&prev_read, pipefd, 0);
				return (1);
			}
		}
		//forkazo
		pid = fork();
		if (pid == -1)
		{
			close_all(&prev_read, pipefd, !is_last);
			return(1);
		}

		//codigo para el hijo
		if (pid == 0)
		{
			//conectar la entrada
			//lee del pipe anterior
			if (prev_read != -1)
			{
				dup2(prev_read, STDIN_FILENO);
				close(prev_read);
			}
			//conectar salida
			//escribir al pipe actual
			if (!is_last)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[0]);
				close(pipefd[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		//codigo del PADRE
		//cerramos lo que no necesitamos
		if (prev_read != -1)
			close(prev_read);
		//guarda la lectura para el siguiente hijo
		if (!is_last)
		{
			close(pipefd[1]);
			prev_read = pipefd[0];
		}
	}
	//esperara a que acaben los procesos hijo
	while (wait(NULL) > 0)
		;
	return (0);
}
