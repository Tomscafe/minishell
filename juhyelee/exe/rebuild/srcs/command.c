/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:44:24 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/16 19:46:02 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_one_command(const t_table table, t_envp *env)
{
	pid_t	child;
	int		status;

	child = fork();
	if (child < 0)
		exit(EXIT_FAILURE);
	else if (child == 0)
	{
		apply_redirection(table);
		execute_at_child(table, env);
	}
	waitpid(child, &status, 0);
	return (WEXITSTATUS(status));
}

void	pipe_command(t_table *table, t_exe *exe, const int input)
{
	if (pipe(table->pipefd) < 0)
		exit(EXIT_FAILURE);
	if (!set_table(table, *exe->cmds->first, input, table->pipefd[WRITE]))
		return ;
	execute_commands(table, exe);
	if (table->is_heredoc)
		unlink("heredoc");
	exe->p_pipe = dup(table->pipefd[READ]);
	close(table->pipefd[READ]);
	close(table->pipefd[WRITE]);
	close_input(*table);
	close_output(*table);
}

void	last_command(t_table *table, t_exe *exe)
{
	if (!set_table(table, *exe->cmds->second, exe->p_pipe, STDOUT_FILENO))
		return ;
	execute_commands(table, exe);
	if (table->is_heredoc)
		unlink("heredoc");
	close_input(*table);
	close_output(*table);
	close(exe->p_pipe);
}

void	execute_commands(t_table *table, t_exe *exe)
{
	signal(SIGINT, SIG_IGN);
	table->pid = fork();
	if (table->pid < 0)
		exit(EXIT_FAILURE);
	else if (table->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (is_builtin(table->command))
		{
			apply_redirection(*table);
			builtin(*table, exe);
		}
		else
			execute_at_child(*table, (const t_envp *)(*exe->env));
		exit(exe->st_exit);
	}
	signal(SIGINT, handler);
}
