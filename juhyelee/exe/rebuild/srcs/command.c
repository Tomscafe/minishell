/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:44:24 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/17 12:04:15 by juhyelee         ###   ########.fr       */
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
		execute_at_child(table, env);
	waitpid(child, &status, 0);
	return (WEXITSTATUS(status));
}

void	pipe_command(t_table *table, t_exe *exe, const size_t index)
{
	if (pipe(table->pipefd) < 0)
		exit(EXIT_FAILURE);
	if (!set_table(table, (const t_exe *)exe, index))
		return ;
	execute_commands(table, exe);
	exe->p_pipe = dup(table->pipefd[READ]);
	close(table->pipefd[READ]);
	close(table->pipefd[WRITE]);
}

void	last_command(t_table *table, t_exe *exe)
{
	if (!set_table(table, exe, exe->n_cmd - 1))
		return ;
	execute_commands(table, exe);
	if (table->is_heredoc)
		unlink("heredoc");
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
			builtin(*table, exe);
		else
			execute_at_child(*table, (const t_envp *)(*exe->env));
		exit(exe->st_exit);
	}
	signal(SIGINT, handler);
}
