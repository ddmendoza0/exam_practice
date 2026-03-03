

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>


int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t	pid;
	int	status;

	//verificaciones
	if (!f)
		return (-1);

	//hacemos  un fork
	pid = fork();
	if (pid == -1)
		return (-1);

	//ejecutamos la funcio
	if (pid == 0)
	{
		alarm(timeout);
		f();
		exit(0);
	}

	//esperamos a que acabe el proceso forkado
	waitpid(pid, &status, 0);

	if (WIFEXITED(status))
	{
		int exit_code = WEXITSTATUS(status);//recogemos el exit code
		if (exit_code == 0)
		{
			if (verbose)
				printf("Nice function!\n");
			return (1);
		}
		else
		{
			if(verbose)
				 printf("Bad function: exited with code %d\n", exit_code);
			return (0);
		}
	}
	else if (WIFSIGNALED(status))
	{
		int sig = WTERMSIG(status);
		if (sig == SIGALRM)
		{
			if(verbose)
				printf("Bad function: timed out after %u seconds\n", timeout);
			return (0);
		}
		else
		{
			if (verbose)
				printf("Bad function: %s\n", strsignal(sig));
			return (0);
		}
	}
	return (-1);
}
