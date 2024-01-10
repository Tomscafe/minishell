/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:34:18 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/09 19:47:48 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_unset(const t_table table, t_execution *exe, const int is_child)
{
	const char	**arg = (const char **)ft_split(table.argument, ' ');

	if (!arg)
	{
		fprintf(stderr, "unset: split error\n");
		exit(EXIT_FAILURE);
	}
	if (is_child)
	{
		close(table.inputfd);
		close(table.outputfd);
	}
	else
	{
		if (table.inputfd != STDIN_FILENO)
			close(table.inputfd);
		if (table.outputfd != STDOUT_FILENO)
			close(table.outputfd);
	}
	unset_core(arg, exe);
}

void	unset_core(const char **arg, t_execution *exe)
{
	size_t	index;

	index = 0;
	while (arg[index])
	{
		remove_env(exe, arg[index]);
		index++;
	}
}

void	remove_env(t_execution *exe, const char *var)
{
	t_envp	*to_del;
	t_envp	*to_del_prev;

	to_del = exe->env;
	while (to_del)
	{
		if (ft_strncmp(to_del->variable, var, ft_strlen(to_del->variable)) == 0)
		{
			to_del_prev = get_to_del_prev(exe, to_del);
			to_del_prev->next = to_del->next;
			free(to_del->variable);
			free(to_del->value);
			free(to_del);
			to_del = to_del_prev->next;
		}
		to_del = to_del->next;
	}
}

t_envp	*get_to_del_prev(t_execution *exe, t_envp *to_del)
{
	t_envp	*prev;

	prev = exe->env;
	while (prev->next != to_del)
		prev = prev->next;
	return (prev);
}

void	process_child(const t_table table, t_execution *exe)
{
	char	*path;
	char	**args;

	path = NULL;
	dup2(table.inputfd, STDIN_FILENO);
	dup2(table.outputfd, STDOUT_FILENO);
	close(table.inputfd);
	close(table.outputfd);
	close_pipe(exe->pipefd);
	if (is_builtin(table.command))
		builtin(table, exe, 1);
	else
	{
		path = is_executable(table);
		if (!path)
			exit(1);
		args = get_args(table);
			exit(1);
		execve(path, args, table.env);
	}
}
