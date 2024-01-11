/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:36:04 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/11 16:01:12 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_at_child(const t_table table, const t_envp *list)
{
	const char	**env = convert_to_array(list);

	if (!is_executable(table.command, env))
	{
		printf("minishell: %s: Not found command\n", table.command);
		exit(EXIT_FAILURE);
	}
	execve(table.command, table.argument, env);
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

int	is_executable(const char *cmd, const char **env)
{
	size_t	index;
	char	**path;
	char	*exe_path;
	int		is_execute;

	path = get_path(env);
	index = 0;
	is_execute = 0;
	while (path[index])
	{
		exe_path = get_exe_path(path[index], cmd);
		if (is_possible(exe_path))
		{
			is_execute = 1;
			free(exe_path);
			break ;
		}
		index++;
		free(exe_path);
	}
	clear_path(path);
	return (is_execute);
}

int	is_possible(const char *cmd_path)
{
	struct stat	status;
	int			mode;

	if (stat(cmd_path, &status) < 0)
		exit(EXIT_FAILURE);
	mode = status.st_mode & 0777;
	return (((mode >> 6) & 1) && ((mode >> 3) & 1) && (mode & 1));
}
