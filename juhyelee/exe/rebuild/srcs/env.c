/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:00:02 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/17 14:48:15 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_string(const t_envp *env)
{
	char	*variable;
	char	*value;
	char	*ret;

	variable = ft_strdup(env->variable);
	if (!variable)
		exit(EXIT_FAILURE);
	value = ft_strjoin("=", env->value);
	if (!value)
		exit(EXIT_FAILURE);
	ret = ft_strjoin(variable, value);
	if (!ret)
		exit(EXIT_FAILURE);
	return (ret);
}

char	**get_paths(const char **env)
{
	size_t	index;
	char	*path;
	char	**ret;

	index = 0;
	path = NULL;
	while (env[index])
	{
		if (ft_strncmp(env[index], "PATH", 4) == 0)
		{
			path = (char *)env[index] + 5;
			break ;
		}
		index++;
	}
	if (!path)
		return (NULL);
	ret = ft_split(env[index] + 5, ':');
	if (!ret)
		exit(EXIT_FAILURE);
	return (ret);
}

char	*get_exe_path(const char *path, const char *cmd)
{
	char	*root;
	char	*ret;

	root = ft_strjoin(path, "/");
	if (!root)
		exit(EXIT_FAILURE);
	ret = ft_strjoin(root, cmd);
	if (!ret)
		exit(EXIT_FAILURE);
	return (ret);
}

void	clear_strs(char **strs)
{
	size_t	index;

	index = 0;
	while (strs[index])
	{
		free(strs[index]);
		index++;
	}
	free(strs);
}

void	add_variable(t_envp **list, const char *var, const char *val)
{
	t_envp	*last;
	t_envp	*new_env;

	last = *list;
	while (last->next)
		last = last->next;
	new_env = (t_envp *)malloc(sizeof(t_envp));
	if (!new_env)
		exit(EXIT_FAILURE);
	new_env->variable = (char *)var;
	new_env->value = (char *)val;
	new_env->next = NULL;
	if (!*list)
		*list = new_env;
	else
		last->next = new_env;
}
