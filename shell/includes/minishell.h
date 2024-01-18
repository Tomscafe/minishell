/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:38:43 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/18 19:44:23 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <dirent.h>
# include <termios.h>
# include <sys/syslimits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define WARD 0
# define COMMAND 1
# define QUOTE 2
# define QUOTES 3
# define REDIRECTION 4
# define PIPE 5
# define SP 6
# define DOLLOR 7
# define ONE_CMD (-1)
# define NO_FILE (-1)
# define READ 0
# define WRITE 1

typedef struct s_envp
{
	char			*variable;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_redirection
{
	char					*symbol;
	char					*file;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_simple
{
	char	*command;
	char	*ward;
}	t_simple;

typedef struct s_command
{
	t_simple		*simple_command;
	t_redirection	*redirection;
}	t_command;

typedef struct s_pipe
{
	t_command		*first;
	t_command		*second;
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_token
{
	char			*str;
	int				type;
	t_envp			*env;
	struct s_token	*next;
}	t_token;

typedef struct s_proc
{
	pid_t	pid;
	char	*cmd;
	char	*arg;
	int		input;
	int		output;
}t_proc;

typedef struct s_file
{
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

typedef struct s_setting
{
	t_list		*files;
	t_command	cmd;
	int			input;
	int			output;
}t_setting;

void			handler(int sig);
void			ft_signal(void);
char			*mini_strdup(char *s, int i, int j);

int				valid_quotes(char *str);
int				check_type(char c);
t_token			*init_token(t_token *token);
void			add_token_back(t_token *token, char *str, int type);
int				ignore_space(char *str, int i, int type);
int				ignore_quotes(char *str, int j, char c);
int				token_command(t_token *token, char *str, int i, int type);
int				end_of_ward(char c);
int				token_ward(t_token *token, char *str, int i, int type);
int				token_redirection(t_token *token, char *str, int i, int type);
int				token_pipe(t_token *token, char *str, int i, int type);
int				token_flag(t_token *token);
void			tokenizer(t_token *token, char *str);

t_pipe			*init_pipe(t_pipe *pipe);
t_command		*init_com(t_command *com);
t_redirection	*init_redirection(t_redirection *rd);
t_token			*add_back_rd(t_token *curr, t_redirection *rd);
t_redirection	*last_redirection(t_redirection *rd);

t_command		*make_command(t_token *front);
t_token			*find_next_front(t_token *front);
t_pipe			*last_pipe(t_pipe *pipe);
t_pipe			*new_pipe(t_pipe *pipe, t_token *front);
t_pipe			*make_pipe_tree(t_pipe *pipe,
					t_pipe *next_pipe, t_token *token, int cnt);

int				valid_redirection(t_token *curr);
int				valid_redirection2(t_token *curr);
int				valid_redirection3(t_token *curr);
int				valid_pipe(t_token *curr);
int				syntax_error(t_token *token);
void			free_simple(t_command *com);
void			free_command(t_command *com);
void			free_pipe(t_pipe *pipe, t_pipe *pipe_next);
void			all_free(t_token *token, t_pipe *pipe);

char			*env_value(char *str);
char			*env_variable(char *str);
t_envp			*new_env(char *str);
t_envp			*make_env(char **envp);

int				dollor_len(char *str, int k, char *variable);
int				check_dollor_opt(char *str, int *i);
char			*convert_dollor(t_envp *needle, char *str, int *i);
int				convertable_dollor(char *str, int i);
char			*check_dollor(t_envp *env, char *str, int i, int flag);
t_envp			*find_dollor(t_envp *needle, char *str, int i);
void			remake_str2(char *result, char *temp, int *k, int *t);
char			*remake_str(char *str, char *temp, int r, int *i);
char			*remove_str(char *str, int i, int j, int t);

int				rm_size_space(char *str, int i, int space, int cnt);
void			quotes_strdup(char *result, char *str, int *i, int *j);
char			*rm_sp_strdup(char *str, int i, int j);
void			copy_result_idx(char *str, char *result, int *i, int *j);
char			*pipe_strdup(t_envp *env, char *str);

int				check_heredoc(char *str);
t_token			*add_back_rd(t_token *curr, t_redirection *rd);
t_redirection	*last_redirection(t_redirection *rd);
t_redirection	*make_redirection(t_token *front);
t_simple		*make_simple_command(t_token *front);

void			get_simple_ward(t_envp *env, t_simple *simple, char *ward);
void			get_command_ward(t_envp *env,
					t_simple *simple, char *file, int j);
void			get_command(t_envp *env, t_simple *simple, char *file);
void			get_ward(t_envp *env, t_simple *simple, char *file);
void			get_simple(t_envp *env, t_simple *simple, t_redirection *rd);

void			get_copy_filename(char *str, char *file, int j, int size);
void			cutting_filename(t_envp *env, t_redirection *rd, char *file);
void			add_split_char(char *result, int *i, int *j);
int				have_others(char *file);
int				file_name_length(char *file, int j);

void			ft_parsing(char *str, t_envp *env);

void			execute(t_pipe *tree, t_envp **list);
size_t			get_num_cmd(const t_pipe *tree);
void			process_one_command(t_exe *exe);
void			process_commands(t_exe *exe);

int				open_all_files(t_exe *exe);
int				open_files(t_exe *exe, const t_redirection *rd);
int				add_heredoc(t_list **files, const char *end);
int				is_exist(const t_list *files, const char *file_name);
void			add_input(t_list **files, const char *file_name);
void			add_output(t_list **files, char *file_name, const int mode);
void			clear_when_signal(void *to_del);
void			clear_file(void *to_del);
char			*get_file_name(char *file_name);

int				heredoc(const char *end);
void			run_heredoc(const char *end, const int hdfile);

int				execute_one_command(const t_proc table, t_exe *exe);
void			pipe_command(t_proc *table, t_exe *exe, const size_t index);
void			last_command(t_proc *table, t_exe *exe);
void			execute_commands(t_proc *table, t_exe *exe, int *pipefd);
void			cmd_signal(int sig);

int				set_proc(t_proc *proc, const t_setting setting);
int				set_redirection(t_proc *proc, const t_list *files, \
								const t_command cmd);
int				set_file(t_proc *proc, const t_list *files, \
						const t_redirection rd);
char			*get_argument(const t_simple cmd);

int				is_builtin(const char *cmd);
void			builtin(const t_proc table, t_exe *exe);

void			execute_at_child(t_proc proc, t_exe *exe, int *pipefd);
void			apply_redir(t_proc proc, int *pipefd);
void			close_file(int fd);
char			**convert_to_array(const t_envp *list);
char			*is_executable(const char *cmd, const char **env);
char			*user_command(const char *cmd);
char			*other_builtin(const char *cmd, const char **env);

int				execute_echo(t_proc table, const char **arg, const int n_exit);
int				get_echo_option(const char *arg);
void			print_arg(const char **arg, const int output, const int n_exit);
void			print_str(const char *str, const int output, const int n_exit);

int				execute_cd(const char *arg, t_envp **list);
char			*set_first_arg(const char *arg, const t_envp *list);
void			change_pwd(t_envp **list);
void			change_oldpwd(t_envp **list);
char			*get_first_arg(const char *arg);
char			*get_home(const t_envp *list);

int				execute_pwd(const t_proc table);

int				execute_export(t_proc table, const char **arg, t_envp **list);
int				print_env_for_export(const t_proc table, const t_envp *list);
char			*get_variable(const char *env);
char			*get_value(const char *env);
int				change_value(t_envp **list, const char *var, const char *val);
void			add_variable(t_envp **list, const char *var, const char *val);

int				execute_unset(const char **arg, t_envp **list);
void			remove_env(t_envp **list, t_envp *to_del);

int				execute_env(const t_proc table, const t_envp *list);

int				execute_exit(const char *arg);

char			*get_env_string(const t_envp *env);
char			**get_paths(const char **env);
char			*get_exe_path(const char *path, const char *cmd);
void			clear_strs(char **strs);

#endif
