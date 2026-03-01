#include <unistd.h>
#include <stdlib.h>

int ft_popen(const char *file, char *const argv[], char type)
{
	int	pipefd[2]; //array para los 2 descriptores
	pid_t	pid; //id del proceso hijo
	
	//Validar los parametros de entrada
	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);

	//Creacion de pipe
	if (pipe(pipefd) == -1) // pipefd[0] == lectura && pipefd[1] == escritura
		return (-1);

	//Creacion proceso hijo
	pid = fork();
	if(pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	if (pid == 0) //codigo para el hijo
	{
		if (type == 'r')
			dup2(pipefd[1], STDOUT_FILENO); //stdout del hijo -> escritura
		else // 'w'
			dup2(pipefd[0], STDIN_FILENO); //stdin del hijo -> lectura
		//Cerrar procesos del hijo
		close(pipefd[0]);
		close(pipefd[1]);

		//Reemplaza proceso hijo con el comando
		execvp(file, argv); //hace return
		exit(1); //si falla el execvp
	}

	//Codigo para el padre pid>0
	if (type == 'r') //Padre va a LEER
	{
		close(pipefd[1]); //Cierra fd de escritura
		return (pipefd[0]); //devuelve lectura para leer del hijo
	}
	else // 'w' Padre va a ESCRIBIR
	{
		close(pipefd[0]); //Cierra fd de lectura
		return (pipefd[1]); //devuelve escritura para enviar al hijo
	}
}
