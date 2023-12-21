#include "libft/libft.h"
#include "minishell.h"
#include <unistd.h>

void    handler(int sig)
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

t_type	*init_line(t_type *line)
{
	line = malloc(sizeof(t_type));
	if (!line)
		exit (-1);
	line->str = NULL;
	line->type = 0;
	line->prev = NULL;
	line->next = NULL;
	return (line);
}

int	check_type(char *str, int i)
{
	if (str[i] == ' ')
		return (SPACE);
	else if (str[i] == '\'')
		return (QUOTE);
	else if (str[i] == '\"')
		return (QUOTES);
	else if (str[i] == ';')
		return (SEMICOLON);
	else if (str[i] == '\\')
		return (BACK);
	else if (str[i] == '$')
		return (DOLLOR);
	else if (str[i] == '<')
		return (INPUT);
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (APPEND);
		else
			return (OUTPUT);
	}
	else if (str[i] == '|')
		return (PIPE);
	return (STRING);
}

void	line_add_back(t_type *curr, t_type *new)
{
	while (curr->next)
		curr = curr->next;
	curr->next = new;
	new->prev = curr;
}

char	*mini_strdup(char *s, int i, int j)
{
	char	*result;
	int		k;
	
	k = 0;
	result = malloc(sizeof(char) * (j - i));
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

int	storage_string(char *str, t_type *line, int i)
{
	t_type	*new;
	int		j;

	if (!line->prev)
		return (2);		//command error;
	new = init_line(new);
	j = i;
	while (!check_type(str, j))
		j++;
	new->str = mini_strdup(str, i, j);
	new->type = STRING;
	line_add_back(line, new);
	return (j);
}

int	storage_token(char *str, t_type *line)
{
	return (0);
}

void	ft_dollor(char *str, t_type *line, int i)
{
	// envp find val -> replace str[i]~str[i+j] ${ } = { }
}

int	ft_space(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}

int	ft_quote_size(char *str, int i, char c)
{
	return (0);	
}

int	ft_quote(char *str, t_type *line, int i, int t)
{
	int		j;
	t_type	*new;

	j = 0;
	if (t == QUOTE)
		j = ft_quote_size(str, i, '\'');
	else if (t == QUOTES)
		j = ft_quote_size(str, i, '\"');
	new = init_line(new);
	if (!new)
		exit (-1);
	new->str = mini_strdup(str, i, j);
	new->type = t;
	return (j);
}

void	make_line(char *str, t_type *line)
{
	int	i;
	int	t;

	i = 0;
	while (str[i])
	{
		t = check_type(str, i);
		if (!t)
			i = storage_string(str, line, i);
		else if (t == SP)
			i = ft_space(str, i);
		else if (t == DOLLOR)
			ft_dollor(str, line, i);
		else if (t == QUOTE || t == QUOTES)
			i = ft_quote(str, line, i, t);
		i = storage_token(str, line);
	}
}

void	ft_parsing(char *str)
{
	t_type	*head;

	head = init_line(head);
	make_line(str, head);
}

void	ft_readline(void)
{
	char	*str;
	t_type	*head;
	t_type	*line;

	while (1)
	{
		str = readline("minishell$ ");
		if (str)
		{
			add_history(str);
			ft_parsing(str);
			free (str);
			str = NULL;
		}
		else if (!str)
		{
			printf("\033[1A");
			printf("\033[10C");
			printf(" exit\n");
			exit(-1);
		}
		else if (*str == '\0')
			free (str);
	}
}

int	main(int ac, char **av, char *envp[])
{
	if (ac != 1)
	{
		printf("error\n");
		return (2);
	}
	ft_signal();
	ft_readline();
	return (0);
}