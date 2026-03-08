

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int	picoshell( char **cmds[])
{
	int	pre = -1; //inicializado en -1 para la primera iteracion
	int	fds[2];
	pid_t	pid;

	//recorremos todos los cmds empalmando salida con entrada
	for (int i = 0; cmds[i]; i++)
	{
		int isl = (cmds[i + 1] == NULL);//es ultimo si el siguiente es nulo
		if (!isl) //abrimos fds con pipe si no es ultimo
		{
			if (pipe(fds) == -1) //si falla y no es el primero tendremos que cerrar el fd previo
			{
				if (pre != -1)
					close(pre);
				return (1);
			}
		}

		pid = fork();//fork
		if (pid == -1)//si falla
		{
			if (pre != -1) //si no es el primero cerramos el previo
				close(pre);
			if (!isl) // si no es ultimo cerramos los fds creados en el pipe
			{
				close(fds[1]);
				close(fds[0]);
			}
			return (1);
		}

		if (pid == 0)// codigo del hijo
		{
			if (pre != -1) //si no es primero empalmamos el fd previo con la entrada
			{
				dup2(pre, STDIN_FILENO);
				close(pre);
			}

			if (!isl) //sino es ultimo empalmamos con la salida
			{
				dup2(fds[1], STDOUT_FILENO);
				close(fds[0]);
				close(fds[1]);
			}
			execvp(cmds[i][0], cmds[i]);//ejecutamos el comando en question
			exit(1);
		}
		
		if (pre != -1) //el padre cierra el previo si no es el primero
			close(pre);
		if (!isl) //cierra el no usado y asigna el fd para el siguiente
		{
			close(fds[1]);
			pre = fds[0];
		}
	}
	while (wait(NULL) > 0)//esperar a todos los subprocesos
		;
	return (0);
}
