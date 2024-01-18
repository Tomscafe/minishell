/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hywoo <hywoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:38:43 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/16 17:38:44 by hywoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define DOLLOR 7

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

#endif
