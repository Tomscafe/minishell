/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:44:24 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/18 12:59:13 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_one_command(const t_proc proc, t_exe *exe)
{
	pid_t	child;
	int		status;

	signal(SIGINT, SIG_IGN);
	child = fork();
	if (child < 0)
		exit(EXIT_FAILURE);
	else if (child == 0)
		execute_at_child(proc, exe, NULL);
	waitpid(child, &status, 0);
	signal(SIGINT, handler);
	return (WEXITSTATUS(status));
}

void	pipe_command(t_proc *proc, t_exe *exe, const size_t index)
{
	t_setting	setting;
	int			pipefd[2];

	if (pipe(pipefd) < 0)
		exit(EXIT_FAILURE);
	setting.files = exe->files;
	setting.cmd = *exe->cmds->first;
	setting.input = exe->p_pipe;
	setting.output = pipefd[WRITE];
	if (index == 0)
		setting.input = STDIN_FILENO;
	if (!set_proc(proc, setting))
		return ;
	execute_commands(proc, exe, pipefd);
	close(exe->p_pipe);
	exe->p_pipe = dup(pipefd[READ]);
	close(pipefd[READ]);
	close(pipefd[WRITE]);
	free(proc->arg);
}

void	last_command(t_proc *proc, t_exe *exe)
{
	t_setting	setting;

	setting.files = exe->files;
	setting.cmd = *exe->cmds->second;
	setting.input = exe->p_pipe;
	setting.output = STDOUT_FILENO;
	if (!set_proc(proc, setting))
		return ;
	execute_commands(proc, exe, NULL);
	close(exe->p_pipe);
	free(proc->arg);
}

void	execute_commands(t_proc *proc, t_exe *exe, int *pipefd)
{
	signal(SIGINT, SIG_IGN);
	proc->pid = fork();
	if (proc->pid < 0)
		exit(EXIT_FAILURE);
	else if (proc->pid == 0)
	{
		signal(SIGINT, cmd_signal);
		if (is_builtin(proc->cmd))
			builtin(*proc, exe);
		else
			execute_at_child(*proc, exe, pipefd);
		exit(exe->st_exit);
	}
	signal(SIGINT, cmd_signal);
}

void	cmd_signal(int sig)
{
	if (sig == SIGINT)
	{
		if (rl_on_new_line() == -1)
			exit (1);
		rl_replace_line("", 1);
	}
}
