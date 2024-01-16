/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 03:41:33 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/16 15:52:57 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_pipe *cmds, t_envp **env)
{
	static t_exe	exe;

	exe.cmds = cmds;
	exe.env = env;
	exe.n_cmd = get_num_cmd(cmds);
	if (exe.n_cmd == 1)
		process_one_command(&exe);
	else
		process_commands(&exe);
}

void	process_one_command(t_exe *exe)
{
	t_table	table;

	if (!set_table(&table, *exe->cmds->first, STDIN_FILENO, STDOUT_FILENO))
	{
		exe->st_exit = EXIT_FAILURE;
		return ;
	}
	if (is_builtin(table.command))
		builtin(table, exe);
	else
		execute_one_command(table, *exe->env);
	if (table.is_heredoc)
		unlink("heredoc");
	close_input(table);
	close_output(table);
}

void	process_commands(t_exe *exe)
{
	t_table	*tables;
	size_t	index;

	
	tables = (t_table *)malloc(sizeof(t_table) * exe->n_cmd);
	if (!tables)
		exit(EXIT_FAILURE);
	pipe_command(&tables[0], exe, STDIN_FILENO);
	index = 1;
	while (exe->cmds->next)
	{
		exe->cmds = exe->cmds->next;
		pipe_command(&tables[index], exe, exe->p_pipe);
		index++;
	}
	if (exe->cmds->second)
		last_command(&tables[index], exe);
	index = 0;
	while (index < exe->n_cmd)
	{
		waitpid(tables[index].pid, &exe->st_exit, WUNTRACED);
		index++;
	}
	free(tables);
}

size_t	get_num_cmd(const t_pipe *cmds)
{
	size_t	n_cmd;

	n_cmd = 1;
	while (cmds->next)
	{
		cmds = cmds->next;
		n_cmd++;
	}
	if (cmds->second)
		n_cmd++;
	return (n_cmd);
}

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

void	apply_redirection(t_table table)
{
	//if (table.input != STDIN_FILENO)
	//{
	//	dup2(table.input, STDIN_FILENO);
	//	close(table.input);
	//}
	//if (table.output != STDOUT_FILENO)
	//{
	//	dup2(table.output, STDOUT_FILENO);
	//	close(table.output);
	//}
	//if (pipefd)
	//{
	//	close(pipefd[0]);
	//	close(pipefd[1]);
	//}
	dup2(table.input, STDIN_FILENO);
	close_input(table);
	dup2(table.output, STDOUT_FILENO);
	close_output(table);
	if (table.pipefd[0] != STDIN_FILENO && table.pipefd[0] != STDOUT_FILENO)
		close(table.pipefd[0]);
	if (table.pipefd[1] != STDIN_FILENO && table.pipefd[1] != STDOUT_FILENO)
		close(table.pipefd[1]);
}