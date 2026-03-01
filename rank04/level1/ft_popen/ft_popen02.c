
#include <stdlib.h>
#include <unistd.h>



int	ft_popen(const char *file, char *const argv[], char type)
{
	//DECLARACION de pipe y fds
	pid_t	pid;
	int	pipefd[2];

	//comprobacion de argumentos
	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);

	//creacion de pipe y verificacion con pipefd
	if (pipe(pipefd) == -1)
		return (-1);

	//fork y verificacion
	pid = fork();
	if (pid == -1)
	{
		//cerramos los pipes y salimos
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	//proceso del hijo
	if (pid == 0)
	{
		//si es operacion de lectura el fd sera el stdout
		if (type == 'r')
			dup2(pipefd[1], STDOUT_FILENO);
		else//si es operacion de escritura el 0 sera entrada estandar
			dup2(pipefd[0], STDIN_FILENO);

		//hacemos limpieza con close y ejecutamos
		close(pipefd[0]);
		close(pipefd[1]);
		execvp(file, argv);
		exit(1);
	}
	//ahora el padre
	if (type == 'r')
	{
		//cerramos el pipe que no vamos a usar y devolvemos el que si
		//1 para lectura
		close(pipefd[1]);
		return(pipefd[0]);
	}
	else
	{
		//0 para escritura
		close(pipefd[0]);
		return(pipefd[1]);
	}
}
