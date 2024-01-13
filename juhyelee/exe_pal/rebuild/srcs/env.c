/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:00:02 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/12 12:59:51 by juhyelee         ###   ########.fr       */
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

int	execute_env(const t_table table, const t_envp *list)
{
	pid_t	child;
	int		exit_num;

	child = fork();
	if (child < 0)
		exit(EXIT_FAILURE);
	else if (child == 0)
	{
		builtin_output(table.input, table.output);
		while (list)
		{
			if (list->value && list->value[0])
			{
				ft_putstr_fd(list->variable, STDOUT_FILENO);
				ft_putchar_fd('=', STDOUT_FILENO);
				ft_putendl_fd(list->value, STDOUT_FILENO);
			}
			list = list->next;
		}
		exit(EXIT_SUCCESS);
	}
	waitpid(child, &exit_num, WUNTRACED);
	return (WEXITSTATUS(exit_num));
}
