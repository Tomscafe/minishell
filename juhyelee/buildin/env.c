#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int	main(int argc, char *argv[], char *envp[])
{
	size_t	index;

	if (argc != 1)
	{
		perror("env is no option");
		exit(EXIT_FAILURE);
	}
	index = 0;
	while (envp[index])
	{
		write(STDOUT_FILENO, envp[index], strlen(envp[index]));
		write(STDOUT_FILENO, "\n", 1);
		index++;
	}
	return (0);
}
