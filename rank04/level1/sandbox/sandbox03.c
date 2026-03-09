
#include <sys/wait.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
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
		exit(0); //fallo - es exit 0 no es error es bien.
	}

	waitpid(pid, &status, 0);

	if (WIFEXITED(status))
	{
		int xs	= WEXITSTATUS(status);
		if (xs == 0)
		{
			if (verbose)
				printf("Nice function!\n");
			return (1);
		}
		if (verbose)
			printf("Bad function: exited with code %i\n", xs);
		return (0);
	}
	else if (WIFSIGNALED(status))
	{
		int	sig = WTERMSIG(status);
		if (sig == SIGALRM)
		{
			if (verbose)
				printf("Bad function: timed out after %i seconds\n", timeout);
			return (0);
		}
		if (verbose)
				printf("Bad function: %s\n", strsignal(sig));
		return (0);
	}
	return (-1); //fallo - retornar -1 no 0.
}
