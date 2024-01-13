/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 03:41:33 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/13 13:28:45 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_pipe *tree, t_envp **list)
{
	pid_t	minishell_execution;

	// builtin ?
	minishell_execution = fork();
	if (minishell_execution < 0)
		return ;
	else if (minishell_execution == 0)
		run_execution(tree, list);
	waitpid(minishell_execution, NULL, WUNTRACED);
}

void	run_execution(t_pipe *tree, t_envp **list)
{
	t_execution	execution;
	t_table		*table;

	execution.tree = tree;
	execution.list = list;
	execution.tree_size = get_tree_size((const t_pipe *)tree);
	table = get_table_list(execution);
}

size_t	get_tree_size(const t_pipe *tree)
{
	size_t	size;

	size = 0;
	while (tree)
	{
		size++;
		tree = tree->next;
	}
	return (size);
}

t_table	*get_table_list(t_execution exe)
{
	t_table	*table_list;
	size_t	index;

	table_list = (t_table *)malloc(sizeof(t_table) * exe.tree_size);
	if (!table_list)
		exit(EXIT_FAILURE);
	index = 0;
	while (index < exe.tree_size)
	{
		table_list[index].index = index;
		table_list[index].command = exe.tree->first->simple_command->command;
		table_list[index].argument = get_argument(*exe.tree->first->simple_command);
		index++;
		exe.tree = exe.tree->next;
	}
	table_list[0].inputdef = STDIN_FILENO;
	table_list[exe.tree_size - 1].outputdef = STDOUT_FILENO;
	return (table_list);
}

/* ----------------------------------------------------------------------------------- */

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
