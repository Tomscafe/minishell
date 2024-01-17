/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:53:01 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/17 22:54:20 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_cd(const char *arg, t_envp **list)
{
	char	*first_arg;

	arg += 3;
	change_oldpwd(list);
	if (arg[0] == '\0')
	{
		chdir(get_home((const t_envp *)(*list)));
		change_pwd(list);
		return (EXIT_SUCCESS);
	}
	first_arg = get_first_arg(arg);
	if (!first_arg)
		exit(EXIT_FAILURE);
	if (chdir(first_arg) < 0)
		return (free(first_arg), EXIT_FAILURE);
	change_pwd(list);
	return (EXIT_SUCCESS);
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

char	*get_home(const t_envp *list)
{
	while (list)
	{
		if (ft_strncmp(list->variable, "HOME", ft_strlen(list->variable)) == 0)
			break ;
		list = list->next;
	}
	if (!list)
		return (NULL);
	return (ft_strdup(list->value));
}
