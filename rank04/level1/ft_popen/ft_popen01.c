
#include <unistd.h>
#include <stdlib.h>

int ft_popen(const char *file, char *const *argv, char type)
{
	//primero declaramos el array de fd y el pid del hijo
	int	pipefd[2]; //array de dos
	pid_t	pid;

	//VALIDATE file, arguments and type
	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);

	//CONEXION pipe creation
	if (pipe(pipefd) == -1) //asigna [0] lectura y [1] escritura
		return (-1);

	//FORK creacion del hijo
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	//EJECUCION codigo para el hijo
	if (pid == 0)
	{
		if (type == 'r') //para lectura asignamos stdout del hijo
			dup2(pipefd[1], STDOUT_FILENO);
		else
			dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execvp(file, argv);
		exit(1);
	}
	
	//codigo para el padre
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
