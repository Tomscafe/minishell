/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 03:41:33 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/13 11:56:50 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_pipe *tree, t_envp **list)
{
	static t_execution	exe;

	exe.tree = tree;
	exe.list = list;
	if (!tree->next && !tree->second)
		exe.exit_num = process_one_command(list, *tree->first, exe.exit_num);
	else
		process_commands(&exe);
}

int	process_one_command(t_envp **list, const t_command cmd, const int n_exit)
{
	t_table	table;
	int		ret;

	if (!set_table(&table, cmd, STDIN_FILENO, STDOUT_FILENO))
		return (EXIT_FAILURE);
	if (is_builtin(table.command))
		ret = builtin(table, list, n_exit);
	else
		ret = execute_one_command(table, *list);
	if (table.is_heredoc)
		unlink("heredoc");
	close_input(table.input, table.indef);
	close_output(table.output, table.outdef);
	return (ret);
}

int	execute_one_command(const t_table table, t_envp *list)
{
	pid_t	child;
	int		status;

	child = fork();
	if (child < 0)
		exit(EXIT_FAILURE);
	else if (child == 0)
	{
		apply_redirection(table);
		execute_at_child(table, list);
	}
	waitpid(child, &status, WUNTRACED);
	return (WEXITSTATUS(status));
}

void	apply_redirection(const t_table table)
{
	if (table.input != STDIN_FILENO)
	{
		dup2(table.input, STDIN_FILENO);
		close(table.input);
	}
	if (table.output != STDOUT_FILENO)
	{
		dup2(table.output, STDOUT_FILENO);
		close(table.output);
	}
}
