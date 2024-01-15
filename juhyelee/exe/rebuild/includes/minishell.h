
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
# include <sys/wait.h>

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
	int		indef;
	int		outdef;
	int		is_heredoc;
}t_table;

typedef struct s_execution
{
	t_pipe	*tree;
	t_envp	**list;
	int		prev;
	int		exit_num;
}t_execution;

void	handler(int sig);
void	ft_signal(void);
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

int		process_one_command(t_envp **list, const t_command cmd, \
							const int n_exit);
int		execute_one_command(const t_table table, t_envp *list);

void	process_commands(t_execution *exe);
void	pipe_command(t_execution *exe, const t_command cmd, const int input);
void	last_command(t_execution *exe, const t_command cmd);
int		execute_commands(const t_table table, t_envp **list, const int n_exit);

int		set_table(t_table *table, const t_command cmd, \
					const int input, const int output);
char	*get_argument(const t_simple cmd);
int		set_redirection(t_table *table, const t_redirection *rd);
int		set_input(t_table *table, const t_redirection *rd);
int		set_output(t_table *table, const t_redirection *rd);
void	close_input(int input, int indef);
void	close_output(int output, int outdef);
int		heredoc(const char *end);
void	run_heredoc(const char *end, const int hdfile);
void	apply_redirection(const t_table table);

void	set_pipe_table(t_table *table, const t_command cmd, \
						const int input, const int *pipefd);
int		set_inputdir(t_table *table, const t_redirection *rd);

int		is_builtin(const char *cmd);
int		builtin(const t_table table, t_envp **list, const int n_exit);
void	builtin_output(int input, int output);

int		execute_echo(t_table table, const int n_exit);
int		get_echo_option(const char *arg);
void	print_arg(const char *str, const int n_exit);

int		execute_cd(const char *arg, t_envp **list);
void	change_pwd(t_envp **list);
void	change_oldpwd(t_envp **list);
char	*get_first_arg(const char *arg);
char	*get_home(const t_envp *list);

int		execute_pwd(const t_table table);

int		execute_export(t_table table, t_envp **list);
int		print_env_for_export(const t_table table, const t_envp *list);
char	*get_variable(const char *env);
char	*get_value(const char *env);
int		change_value(t_envp **list, const char *var, const char *val);
void	add_variable(t_envp **list, const char *var, const char *val);

int		execute_unset(const char *arg, t_envp **list);
void	remove_env(t_envp **list, t_envp *to_del);

int		execute_env(const t_table table, const t_envp *list);

int		execute_exit(const char *arg);

void	execute_at_child(const t_table table, const t_envp *list);
char	**convert_to_array(const t_envp *list);
char	*is_executable(const char *cmd, const char **env);
char	*user_command(const char *cmd);
char	*other_builtin(const char *cmd, const char **env);

char	*get_env_string(const t_envp *env);
char	**get_paths(const char **env);
char	*get_exe_path(const char *path, const char *cmd);
void	clear_strs(char **strs);

#endif
