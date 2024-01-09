/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:49:26 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/09 19:39:25 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_pipe pipe)
{
	t_execution	exe;

	process_first_command(&exe);
	process_middle_command(&exe);
	process_last_command(&exe);
}

void	process_first_command(t_execution *exe)
{
	t_table	table;

	table.command = exe->tree->first->simple_command->command;
	table.argument = exe->tree->first->simple_command->ward;
	table.env = set_env(exe->env);
	if (!table.env)
		return ;
	table.inputfd = STDIN_FILENO;
	if (!exe->tree->second && is_builtin(table.command))
	{
		table.outputfd = STDOUT_FILENO;
		if (set_redirection(&table, exe->tree->first->redirection))
			builtin(table, exe, PARENT);
	}
	else
	{
		if (pipe(exe->pipefd) == -1)
		{
			fprintf(stderr, "process first command: pipe fail\n");
			return ;
		}
		table.outputfd = exe->pipefd[WRITE];
		if (set_redirection(&table, exe->tree->first->redirection))
			execute_at_child(table, exe);
		exe->prevfd = dup(exe->pipefd[READ]);
		close_pipe(exe->pipefd);
	}
}

void	process_middle_command(t_execution *exe)
{
	t_table	table;

	while (exe->tree->next)
	{
		table.command = exe->tree->second->simple_command->command;
		table.argument = exe->tree->second->simple_command->ward;
		table.env = set_env(exe->env);
		table.inputfd = exe->prevfd;
		if (pipe(exe->pipefd) == -1)
		{
			fprintf(stderr, "process middle command: pipe fail\n");
			continue ;
		}
		if (set_redirection(&table, exe->tree->second->redirection))
			execute_at_child(table, exe);
		exe->tree = exe->tree->next;
		exe->prevfd = dup(exe->pipefd[READ]);
		close_pipe(exe->pipefd);
	}
}

void	process_last_command(t_execution *exe)
{
	t_table	table;

	if (exe->tree->second)
	{
		table.command = exe->tree->second->simple_command->command;
		table.argument = exe->tree->second->simple_command->ward;
		table.inputfd = exe->prevfd;
		table.outputfd = STDOUT_FILENO;
		if (set_redirection(&table, exe->tree->second->redirection))
			execute_at_child(table, exe);
	}
	close(exe->prevfd);
}

void	execute_at_child(const t_table table, t_execution *exe)
{
	pid_t	child;
	char	*path;

	child = fork();
	if (child == -1)
	{
		fprintf(stderr, "execute at child: fail to fork\n");
		return ;
	}
	else if (child == 0)
		process_child(table, exe);
	wait(NULL);
	exe->prevfd = dup(exe->pipefd[READ]);
	close_pipe(exe->pipefd);
}
