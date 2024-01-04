/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:20:06 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/04 14:09:25 by juhyelee         ###   ########.fr       */
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

// 환경 변수는 내부에서 어떻게 구조를 이루고 있는지.
// 우선 배열로 환경 변수를 관리했지만, 해시로 한다고 한다면 해시 관련 API를 만들어 적용
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
void	unset_cmd(const size_t argc, const char *argv[], char *envs[]);
void	env_cmd(const char *envs[]);
char	**export_cmd(const size_t argc, const char *argv[], const char *envs[]);

#endif
