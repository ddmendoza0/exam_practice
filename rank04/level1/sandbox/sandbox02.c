
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	pid_t	pid;
	int	status;

	if (!f)
		return (-1);

	pid = fork();
	if (pid == -1)
		return (-1);

	if (pid == 0)
	{
		alarm(timeout);
		f();
		exit(0);
	}

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		int es = WEXITSTATUS(status); //mucha atencion a las funciones de senyales
		if (es == 0)
		{
			if (verbose)
				printf("Nice function\n");
			return (1);
		}
		if (verbose)
			printf("Bad function: exited with code %d\n", es);
		return (0);
	}
	else if (WIFSIGNALED(status))
	{
		int sig = WTERMSIG(status);
		if (sig == SIGALRM)
		{
			if (verbose)
				printf("Bad function: timed out after %d seconds\n", timeout);
			return (0);
		}
		if (verbose)
			printf("Bad function: %s\n", strsignal(sig));
		return (0);
	}
	return (-1);
}
