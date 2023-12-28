
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define WARD 0
# define COMMAND 1
# define QUOTE 2
# define QUOTES 3
# define REDIRECTION 4
# define PIPE 5
# define SP 6

typedef struct	s_redirection
{
	char					*symbol;
	char					*file;
	struct s_redirection	*next;
}	t_redirection;

typedef struct	s_simple
{
	char	*command;
	char	*ward;
}	t_simple;

typedef struct	s_command
{
	t_simple		*simple_command;
	t_redirection	*redirection;
}	t_command;

typedef struct	s_pipe
{
	t_command		*first;
	t_command		*second;
	struct s_pipe	*next;
}	t_pipe;

typedef struct	s_token
{
	char		*str;
	int			type;
	struct s_token	*next;
}	t_token;

void	handler(int sig);
void	ft_signal(void);
char	*mini_strdup(char *s, int i, int j);

int	valid_quotes(char *str);
int	check_type(char c);
t_token	*init_token(t_token *token);
void	add_token_back(t_token *token, char *str, int type);
int	ignore_space(char *str, int i, int type);
int	ignore_quotes(char *str, int j, char c);
int	token_command(t_token *token, char *str, int i, int type);
int	end_of_ward(char c);
int	token_ward(t_token *token, char *str, int i, int type);
int	token_redirection(t_token *token, char *str, int i, int type);
int	token_pipe(t_token *token, char *str, int i, int type);
int	token_flag(t_token *token);
void	tokenizer(t_token *token, char *str);

void	ft_parsing(char *str);

#endif