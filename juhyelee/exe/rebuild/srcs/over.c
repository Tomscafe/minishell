/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   over.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:35:43 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/16 00:46:09 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_commands(t_exe *exe)
{
	t_table	*tables;
	size_t	index;

	tables = (t_table *)malloc(sizeof(t_table) * exe->tree_size);
	if (!tables)
		exit(EXIT_FAILURE);
	pipe_command(&tables[0], exe, STDIN_FILENO);
	index = 1;
	while (exe->tree->next)
	{
		exe->tree = exe->tree->next;
		pipe_command(&tables[index], exe, exe->prev);
		index++;
	}
	if (exe->tree->second)
		last_command(&tables[index], exe);
	index = 0;
	while (index < exe->tree_size)
	{
		waitpid(tables[index].pid, &exe->exit_num, WUNTRACED);
		index++;
	}
	free(tables);
}

void	pipe_command(t_table *table, t_exe *exe, const int input)
{
	int		pipefd[2];

	if (pipe(pipefd) < 0)
		exit(EXIT_FAILURE);
	if (!set_table(table, *exe->tree->first, input, pipefd[WRITE]))
		return ;
	execute_commands(table, exe, pipefd);
	if (table->is_heredoc)
		unlink("heredoc");
	exe->prev = dup(pipefd[READ]);
	close(pipefd[READ]);
	close(pipefd[WRITE]);
	close_input(table->input);
	close_output(table->output);
}

void	last_command(t_table *table, t_exe *exe)
{
	if (!set_table(table, *exe->tree->second, exe->prev, STDOUT_FILENO))
		return ;
	execute_commands(table, exe, NULL);
	if (table->is_heredoc)
		unlink("heredoc");
	close_input(table->input);
	close_output(table->output);
	close(exe->prev);
}

void	execute_commands(t_table *table, t_exe *exe, int *pipefd)
{
	int		ret_exit;

	ret_exit = 0;
	signal(SIGINT, SIG_IGN);
	table->pid = fork();
	if (table->pid < 0)
		exit(EXIT_FAILURE);
	else if (table->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		ret_exit = EXIT_SUCCESS;
		apply_redirection(*table, pipefd);
		if (is_builtin(table->command))
			ret_exit = builtin(*table, exe->list, exe->exit_num);
		else
			execute_at_child(*table, (const t_envp *)(*exe->list));
		exit(ret_exit);
	}
	signal(SIGINT, handler);
}
