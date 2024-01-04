/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:20:06 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/04 10:25:27 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDIN_H
# define BUILDIN_H

# include "libft.h"
# include <stdio.h>

# define BUFFER_SIZE 2048
# define FAIL 1

int		check_echo_option(const char *option);
int		check_option(const char *option);
void	print_error(const char *cmd, const char *message, const char *arg);

int		del_envs(char *envs[], const char *env);
char	**dup_envs(const char *envp[]);
char	**add_envs(const char *envs[], const char *env);

int		copy_envs(char *new_envs[], const char *org_envs[]);
char	**create_new_envs(const size_t size);
void	clear_envs(char *envs[]);
size_t	get_envs_size(const char *envs[]);
size_t	find_env(const char *envs[], const char *env);

int		echo_cmd(const size_t argc, const char *argv[]);
int		cd_cmd(const size_t argc, const char *argv[]);
int		exit_cmd(const size_t argc, const char *argv[]);
void	pwd_cmd(void);

int		contain_equ(const char *env);
void	env_cmd(const char *envs[]);
char	**export_cmd(const size_t argc, const char *argv[], const char *envs[]);

#endif
