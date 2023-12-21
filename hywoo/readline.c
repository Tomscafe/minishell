#include "minishell.h"
// -lreadline -L/Users/hywoo/.brew/opt/readline/lib -I/Users/hywoo/.brew/opt/readline/include
// -lreadline -L/goinfre/hywoo/.brew/opt/readline/lib -I/goinfre/hywoo/.brew/opt/readline/include

void	handler(int sig)
{
	printf("minishell$ \n");

	if (rl_on_new_line() == -1)	// move new line after print read line
		exit (1);
	rl_replace_line("", 1);	// can't fine funtion? works well
	rl_redisplay();			//readline(str) :: display str
}

int	main(int ac, char **av)
{
	char	*str;
	struct	termios	term;

	tcgetattr(STDIN_FILENO, &term);	// init termios (fd, optional_actions, termios_p);
								//optional_actions : TCSNOW TCSADRAIN TCSAFLUSH
	term.c_lflag &= ~(ECHOCTL);	//c_iflag c_oflag c_cflag c_lflag c_cc
								// c_lflag -> control character ^X : off ~(ECHOCTL)
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
								// TCSANOW : change terminal properties
	signal(SIGINT, handler);	// ctr + c : handler(SIGINT)
	signal(SIGQUIT, SIG_IGN);	// ctr + / : signal ignore (SIG_IGN)
	//signal(SIGTERM, handler);	// ctr + d : can't handle sigterm
	while (1)
	{
		str = readline("minishell$ ");
		if (str)
		{
			add_history(str);
			free (str);
			str = NULL;
		}
		else if (!str)
		{
			printf("\033[1A");	// cursor move up 1 line
			printf("\033[10C");	// cursor move forward 10 lines
			printf(" exit\n");
			exit(-1);
		}
		else if (*str == '\0')
			free (str);
	}
	return (0);
}