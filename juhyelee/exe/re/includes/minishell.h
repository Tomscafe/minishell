
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
//# include "libft/libft.h"

/*juhyelee*/
# include "libft.h"
# include <fcntl.h>
# include <sys/stat.h>

# define WARD 0
# define COMMAND 1
# define QUOTE 2
# define QUOTES 3
# define REDIRECTION 4
# define PIPE 5
# define SP 6

/*juhyelee*/
# define CHILD 1
# define PARENT 0
# define WRITE 1
# define READ 0

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

typedef struct	s_envp
{
	char		*variable;
	char		*value;
	struct s_envp	*next;
}	t_envp;

/*juhyelee : execute structures*/
typedef struct s_table
{
	char	*command;
	char	*argument;
	int		input;
	int		output;
}t_table;
typedef struct s_execution
{
	t_pipe	*tree;
	t_envp	**list;
	int		prev;
	int		exit_num;
}t_execution;

//void	handler(int sig);
//void	ft_signal(void);
//char	*mini_strdup(char *s, int i, int j);

//int	valid_quotes(char *str);
//int	check_type(char c);
//t_token	*init_token(t_token *token);
//void	add_token_back(t_token *token, char *str, int type);
//int	ignore_space(char *str, int i, int type);
//int	ignore_quotes(char *str, int j, char c);
//int	token_command(t_token *token, char *str, int i, int type);
//int	end_of_ward(char c);
//int	token_ward(t_token *token, char *str, int i, int type);
//int	token_redirection(t_token *token, char *str, int i, int type);
//int	token_pipe(t_token *token, char *str, int i, int type);
//int	token_flag(t_token *token);
//void	tokenizer(t_token *token, char *str);

//void	ft_parsing(char *str);

/*juhyelee*/
void	execute(t_pipe *tree, t_envp **list);

int		process_one_command(t_envp **list, const t_command cmd, const int n_eixt);
int		execute_one_command(const t_table table, t_envp *list);

void	apply_redirection(const int input, const int output);

#endif
