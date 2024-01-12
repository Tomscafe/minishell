/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 03:41:33 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/12 13:32:08 by juhyelee         ###   ########.fr       */
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
	close_input(table.input);
	close_output(table.output);
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
		apply_redirection(table.input, table.output);
		execute_at_child(table, list);
	}
	waitpid(child, &status, WUNTRACED);
	return (WEXITSTATUS(status));
}

void	apply_redirection(const int input, const int output)
{
	if (input != STDIN_FILENO)
	{
		dup2(input, STDIN_FILENO);
		close(input);
	}
	if (output != STDOUT_FILENO)
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}
}
