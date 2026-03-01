
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	//declaracion
	pid_t	pid;
	int	status;
	int	result;

	//comprobacion de argumento
	if (!f)
		return (-1);

	//forkando
	pid = fork();
	if (pid == -1)
		return (-1);

	//HIJO
	if (pid == 0)
	{
		alarm(timeout); //controla el timeout
		f(); //corremos la funcion
		exit(0);
	}

	//PADRE
	waitpid(pid, &status, 0);
	//ejecucion correcta
	if (WIFEXITED(status))
	{
		//recogemos el exit code
		int	exit_code = WEXITSTATUS(status);
		if (exit_code == 0)// sin errores
		{
			if (verbose)
				printf("Nice function!\n");
			result = 1;
		}
		else//con errores
		{
			if (verbose)
				printf("Bad function: exited with code %d\n", exit_code);
			result = 0;
		}
	}
	else if (WIFSIGNALED(status)) //terminado por senyal
	{
		int	sig = WTERMSIG(status);
		if (sig == SIGALRM)
		{	if (verbose)
				printf("Bad function: timed out after %u seconds\n", timeout);
			result = 0;
		}
		else
		{
			if (verbose)
				printf("Bad function: %s\n", strsignal(sig));
			result = 0;
		}
	}
	else
		result = -1;
	return (result);
}



