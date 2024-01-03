/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:20:06 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/03 21:43:12 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDIN_H
# define BUILDIN_H

# include "libft.h"
# include <stdio.h>

# define BUFFER_SIZE 2048
# define FAIL 1

typedef struct s_env
{
	char			*env;
	char			*val;
}t_env;

int		check_echo_option(const char *option);
int		check_option(const char *option);
void	convert_env_list(t_list **list, const char *envp[]);
void	print_error(const char *cmd, const char *message, const char *arg);
void	add_env(t_list **env_list, const char *str);
void	clear_strs(char **strs);
void	clear_env(t_env *env);
t_env	*create_env(const char *str);

int		echo_cmd(const size_t argc, const char *argv[]);
int		cd_cmd(const size_t argc, const char *argv[]);
int		exit_cmd(const size_t argc, const char *argv[]);
void	export_cmd(t_list **env_list, const size_t argc, const char *argv[]);
void	unset_cmd(t_list **env_list, const size_t argc, const char *argv[]);
void	print_envs(t_list *env_list);
void	reg_envs(t_list **env_list, const size_t argc, const char *argv[]);
void	pwd_cmd(void);
void	env_cmd(t_list *env_list);

#endif
