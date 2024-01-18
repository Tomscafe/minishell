/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:53:01 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/18 18:08:34 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_cd(const char *arg, t_envp **list)
{
	char	*first_arg;

	first_arg = set_first_arg(arg, (const t_envp *)(*list));
	change_oldpwd(list);
	if (!first_arg)
		exit(EXIT_FAILURE);
	if (chdir(first_arg) < 0)
	{
		free(first_arg);
		return (EXIT_FAILURE);
	}
	change_pwd(list);
	free(first_arg);
	return (EXIT_SUCCESS);
}

char	*set_first_arg(const char *arg, const t_envp *list)
{
	char	*home;
	char	*ret;

	home = get_home(list);
	if (!arg)
		return (home);
	else if (arg[0] == '~')
	{
		ret = ft_strjoin(home, arg + 1);
		if (!ret)
			exit(EXIT_FAILURE);
	}
	else if (opendir(arg) == NULL)
	{
		printf("minishell: cd: %s: no such file or directory\n", arg);
		free(home);
		return (NULL);
	}
	else
		ret = get_first_arg(arg);
	free(home);
	return (ret);
}

void	change_pwd(t_envp **list)
{
	char	buffer[2024];
	t_envp	*pwd;

	pwd = *list;
	while (pwd)
	{
		if (ft_strncmp(pwd->variable, "PWD", ft_strlen(pwd->variable)) == 0)
			break ;
		pwd = pwd->next;
	}
	free(pwd->value);
	if (!getcwd(buffer, 2024))
		return ;
	pwd->value = ft_strdup(buffer);
	if (!pwd->value)
		exit(EXIT_FAILURE);
}

void	change_oldpwd(t_envp **list)
{
	char	buffer[2024];
	t_envp	*oldpwd;

	if (!getcwd(buffer, 2024))
		return ;
	oldpwd = *list;
	while (oldpwd)
	{
		if (ft_strncmp(oldpwd->variable, "OLDPWD", \
						ft_strlen(oldpwd->variable)) == 0)
		{
			free(oldpwd->value);
			oldpwd->value = ft_strdup(buffer);
			if (!oldpwd->value)
				exit(EXIT_FAILURE);
		}
		oldpwd = oldpwd->next;
	}
}

char	*get_first_arg(const char *arg)
{
	size_t	size;
	char	*ret;

	size = 0;
	while (arg[size] && arg[size] != ' ')
		size++;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		exit(EXIT_FAILURE);
	ft_strlcpy(ret, arg, size + 1);
	return (ret);
}
