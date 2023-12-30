#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(int argc, char *argv[])
{
	size_t	index;

	if (argc > 2)
	{
		perror("echo is no option");
		exit(EXIT_FAILURE);
	}
	index = 1;
	while (index < (size_t)argc)
	{
		write(STDOUT_FILENO, argv[index], strlen(argv[index]));
		index++;
	}
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
