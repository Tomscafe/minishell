/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:53:01 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/19 19:27:14 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_cd(const char *arg, t_exe *exe)
{
	char	*first_arg;

	change_env("OLDPATH", exe);
	first_arg = set_first_arg(arg, exe);
	if (!first_arg)
		return (EXIT_FAILURE);
	if (!opendir(first_arg))
	{
		printf("minishell : cd: %s:no such file or directory\n", first_arg);
		return (free(first_arg), EXIT_FAILURE);
	}
	if (chdir(first_arg) < 0)
	{
		free(first_arg);
		chdir(exe->pwd_pth);
	}
	ft_strlcpy(exe->pwd_pth, first_arg, PATH_MAX);
	free(first_arg);
	return (EXIT_SUCCESS);
}

char	*set_first_arg(const char *arg, t_exe *exe)
{
	char	*ret;

	ret = get_home_path(arg, *exe->env);
	if (!ret)
	{
		ret = ft_strdup(arg);
		if (!ret)
			exit(EXIT_FAILURE);
	}
	return (ret);
}

char	*get_home_path(const char *arg, const t_envp *list)
{
	char	*ret;
	char	*home;
	size_t	size;

	ret = NULL;
	home = get_home(list);
	if (!home)
		return (NULL);
	if (!arg)
		ret = ft_strdup(home);
	else if (arg[0] == '~')
	{
		size = ft_strlen(home) + ft_strlen(arg + 1) + 1;
		ret = (char *)malloc(sizeof(char) * size);
		if (!ret)
			exit(EXIT_FAILURE);
		ft_strlcpy(ret, home, size);
		ft_strlcat(ret, arg + 1, size);
		free(home);
	}
	free(home);
	return (ret);
}

void	change_env(const char *env, t_exe *exe)
{
	char	buffer[2024];
	t_envp	*oldpwd;

	if (!getcwd(buffer, 2024))
		return ;
	oldpwd = *exe->env;
	while (oldpwd)
	{
		if (ft_strncmp(oldpwd->variable, env, \
						ft_strlen(oldpwd->variable)) == 0)
		{
			free(oldpwd->value);
			oldpwd->value = ft_strdup(exe->pwd_pth);
			if (!oldpwd->value)
				exit(EXIT_FAILURE);
			return ;
		}
		oldpwd = oldpwd->next;
	}
}
