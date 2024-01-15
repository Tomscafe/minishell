/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 03:41:33 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/16 00:45:50 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_pipe *tree, t_envp **list)
{
	static t_exe	exe;

	exe.tree = tree;
	exe.list = list;
	exe.tree_size = 1;
	while (tree->next)
	{
		tree = tree->next;
		exe.tree_size++;
	}
	if (tree->second)
		exe.tree_size++;
	if (exe.tree_size == 1)
		process_one_command(&exe);
	else
		process_commands(&exe);
}

void	process_one_command(t_exe *exe)
{
	t_table	table;

	if (!set_table(&table, *exe->tree->first, STDIN_FILENO, STDOUT_FILENO))
	{
		exe->exit_num = EXIT_FAILURE;
		return ;
	}
	if (is_builtin(table.command))
		exe->exit_num = builtin(table, exe->list, exe->exit_num);
	else
		exe->exit_num = execute_one_command(table, *exe->list);
	if (table.is_heredoc)
		unlink("heredoc");
	close_input(table.input);
	close_output(table.output);
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
		apply_redirection(table, NULL);
		execute_at_child(table, list);
	}
	waitpid(child, &status, 0);
	return (WEXITSTATUS(status));
}

void	apply_redirection(const t_table table, int *pipefd)
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
	if (pipefd)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}
