
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
# define ONE_CMD (-1)
# define NO_FD (-1)
# define HD_SIG (-2)

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
	pid_t	pid;
	char	*command;
	char	*argument;
	int		input;
	int		output;
	int		is_heredoc;
	int		is_signal;
	int		pipefd[2];
}t_table;
typedef struct s_file
{
	int		is_heredoc;
	int		is_signal;
	int		io[2];
	char	*name;
}t_file;
typedef struct s_exe
{
	t_pipe	*cmds;
	t_envp	**env;
	t_list	*files;
	size_t	n_cmd;
	int		p_pipe;
	int		st_exit;
}t_exe;

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

/*
*  ls -al > outfile | cat < outfile 을 하고 나서, cat < outfile을 했을 때, outfile을 찾을 수 없음.
*  cat < "없는 파일"을 했을 때, 없는 파일이라고 뜨지 않고, 그냥 cat이 실행됨.
*/

/* juhyelee */
/* execute part */
void	execute(t_pipe *tree, t_envp **list);
size_t	get_num_cmd(const t_pipe *tree);
void	process_one_command(t_exe *exe);
void	process_commands(t_exe *exe);
/* commands */
int		execute_one_command(const t_table table, t_envp *list);
void	pipe_command(t_table *table, t_exe *exe, const size_t index);
void	last_command(t_table *table, t_exe *exe);
void	execute_commands(t_table *table, t_exe *exe);
/* file */
void	open_all_files(t_exe *exe);
void	open_files(t_exe *exe, const t_redirection *rd);
void	open_heredoc(t_list **list, const char *file_name);
void	open_exist_file(t_list **list, const char *file_name);
void	create_new_file(t_list **list, const char *file_name, const int mode);
void	clear_file(void *to_del);
char	*get_infile(const t_redirection *rd, int *is_heredoc);
char	*get_outfile(const t_redirection *rd, int *is_append);
/* child */
void	execute_at_child(t_table table, const t_envp *list);
char	**convert_to_array(const t_envp *list);
char	*is_executable(const char *cmd, const char **env);
char	*user_command(const char *cmd);
char	*other_builtin(const char *cmd, const char **env);
/* setting */
int		set_table(t_table *table, const t_exe *exe, const int index);
int		set_redirection(t_table *table, const t_list *files, t_command cmd);
int		set_file(t_table *table, const t_list *files, const t_redirection rd);
char	*get_argument(const t_simple cmd);
/* close */
void	close_input(t_table table);
void	close_output(t_table table);
/* heredoc */
int		heredoc(const char *end);
void	run_heredoc(const char *end, const int hdfile);
/* builtin */
int		is_builtin(const char *cmd);
void	builtin(const t_table table, t_exe *exe);
/* echo */
int		execute_echo(t_table table, const int n_exit);
int		get_echo_option(const char *arg);
void	print_arg(const char *str, const int output, const int n_exit);
/* cd */
int		execute_cd(const char *arg, t_envp **list);
void	change_pwd(t_envp **list);
void	change_oldpwd(t_envp **list);
char	*get_first_arg(const char *arg);
char	*get_home(const t_envp *list);
/* pwd */
int		execute_pwd(const t_table table);
/* export */
int		execute_export(t_table table, t_envp **list);
int		print_env_for_export(const t_table table, const t_envp *list);
char	*get_variable(const char *env);
char	*get_value(const char *env);
int		change_value(t_envp **list, const char *var, const char *val);
void	add_variable(t_envp **list, const char *var, const char *val);
/* unset */
int		execute_unset(const char *arg, t_envp **list);
void	remove_env(t_envp **list, t_envp *to_del);
/* env */
int		execute_env(const t_table table, const t_envp *list);
/* exit */
int		execute_exit(const char *arg);
/* envirment */
char	*get_env_string(const t_envp *env);
char	**get_paths(const char **env);
char	*get_exe_path(const char *path, const char *cmd);
void	clear_strs(char **strs);

#endif
