
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
	char	**env;
	int		inputfd;
	int		outputfd;
}t_table;
typedef struct s_execution
{
	t_pipe	*tree;
	t_envp	*env;
	int		pipefd[2];
	int		prevfd;
}t_execution;

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

/*juhyelee*/
void	execute(t_pipe *pipe, t_envp *env);
void	process_first_command(t_execution *exe);
void	process_middle_command(t_execution *exe);
void	process_last_command(t_execution *exe);
void	execute_at_child(const t_table table, t_execution *exe);
void	process_child(const t_table table, t_execution *exe);

char	**get_args(const t_table table);
size_t	get_strs_size(const char **strs);
char	**init_args(const char **arg);
void	copy_strs(char **dest, const char **org);

char	**set_env(const t_envp *envp_list);
size_t	get_env_list_size(const t_envp *envp_list);
char	*set_value(const t_envp *const envp_list);
void	clear_strs(char **strs);

int		set_redirection(t_table *table, const t_redirection *rd);
int		heredoc(const char *end_point);
char	*is_executable(const t_table table);

void	builtin(t_table table, t_execution *exe, const int is_child);
int		is_builtin(const char *command);

void	run_echo(const t_table table, const int is_child);
void	echo_core(const char **arg);
int		set_option(const char *arg);

void	run_cd(const t_table table, const int is_child);
void	cd_core(const char **arg);

void	run_exit(const t_table table, const int is_child);
void	run_pwd(const t_table table, const int is_child);
void	run_export(const t_table table, t_execution *exe, const int is_child);
void	export_core(const char **arg, t_execution *exe);
int		add_env(t_execution *exe, const char *str);
void	set_new_env(t_envp *new_env, const char **value);

void	run_unset(const t_table table, t_execution *exe, const int is_child);
void	unset_core(const char **arg, t_execution *exe);
void	remove_env(t_execution *exe, const char *var);
t_envp	*get_to_del_prev(t_execution *exe, t_envp *to_del);
void	run_env(const t_table table, const t_execution exe, const int is_child);
void	print_env(const t_envp *envp);

void	close_pipe(int *pipe);

#endif