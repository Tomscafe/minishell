/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:36:04 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/11 20:20:29 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_at_child(const t_table table, const t_envp *list)
{
	const char	**env = (const char **)convert_to_array(list);
	const char	**arg = (const char **)ft_split(table.argument, ' ');
	char		*path;

	path = is_executable(table.command, env);
	if (!path)
	{
		printf("minishell: %s: Not found command\n", table.command);
		exit(EXIT_FAILURE);
	}
	execve(path, (char *const *)arg, (char *const *)env);
	clear_strs((char **)env);
	clear_strs((char **)arg);
	free(path);
}

char	**convert_to_array(const t_envp *list)
{
	char			**ret;
	size_t			size;
	size_t			index;
	const t_envp	*p = list;

	size = 0;
	while (p)
	{
		size++;
		p = p->next;
	}
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ret)
		exit(EXIT_FAILURE);
	index = 0;
	while (list)
	{
		ret[index] = get_env_string(list);
		index++;
		list = list->next;
	}
	ret[index] = NULL;
	return (ret);
}

char	*is_executable(const char *cmd, const char **env)
{
	size_t	index;
	char	**path;
	char	*exe_path;

	path = get_paths(env);
	index = 0;
	while (path[index])
	{
		exe_path = get_exe_path(path[index], cmd);
		if (access(exe_path, X_OK) == 0)
			return (exe_path);
		index++;
		free(exe_path);
	}
	clear_strs(path);
	return (NULL);
}
