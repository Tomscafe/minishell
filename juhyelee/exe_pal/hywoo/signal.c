#include "minishell.h"

void	handler(int sig)
{
	printf("minishell$ \n");
	if (rl_on_new_line() == -1)
		exit (1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void	ft_signal(void)
{
	struct	termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

char	*mini_strdup(char *s, int i, int j)
{
	char	*result;
	int		k;
	
	k = 0;
	result = malloc(sizeof(char) * (j - i + 1));
	if (!result)
		exit (-1);
	while (i + k < j)
	{
		result[k] = s[i + k];
		k++;
	}
	result[k] = 0;
	return (result);
}