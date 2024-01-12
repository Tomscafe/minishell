/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   over.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:35:43 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/12 19:30:44 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_commands(t_execution *exe)
{
	pipe_command(exe, *exe->tree->first, STDIN_FILENO);
	while (exe->tree->next)
	{
		exe->tree = exe->tree->next;
		pipe_command(exe, *exe->tree->first, exe->prev);
	}
	if (exe->tree->second)
		last_command(exe, *exe->tree->second);
}

void	pipe_command(t_execution *exe, const t_command cmd, const int input)
{
	t_table	table;
	int		pipefd[2];

	if (pipe(pipefd) < 0)
		exit(EXIT_FAILURE);
	if (!set_table(&table, cmd, input, pipefd[WRITE]))
		return ;
	exe->exit_num = execute_commands(table, exe->list, exe->exit_num);
	exe->prev = dup(pipefd[READ]);
	close_input(table.input, table.indef);
	close_output(table.output, table.outdef);
	close(pipefd[READ]);
	close(pipefd[WRITE]);
}

void	last_command(t_execution *exe, const t_command cmd)
{
	t_table	table;

	if (!set_table(&table, cmd, exe->prev, STDOUT_FILENO))
		return ;
	exe->exit_num = execute_commands(table, exe->list, exe->exit_num);
	close(exe->prev);
	close_input(table.input, table.indef);
	close_output(table.output, table.outdef);
}

int	execute_commands(const t_table table, t_envp **list, const int n_exit)
{
	pid_t	child;
	int		ret_exit;
	int		st_exit;

	ret_exit = 0;
	child = fork();
	if (child < 0)
		exit(EXIT_FAILURE);
	else if (child == 0)
	{
		apply_redirection(table);
		if (is_builtin(table.command))
			ret_exit = builtin(table, list, n_exit);
		else
			execute_at_child(table, (const t_envp *)(*list));
		exit(ret_exit);
	}
	waitpid(child, &st_exit, WUNTRACED);
	ret_exit = WEXITSTATUS(st_exit);
	return (ret_exit);
}
