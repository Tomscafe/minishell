/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:44:24 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/18 00:50:26 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_one_command(const t_proc proc, t_envp *env)
{
	pid_t	child;
	int		status;

	signal(SIGINT, SIG_IGN);
	child = fork();
	if (child < 0)
		exit(EXIT_FAILURE);
	else if (child == 0)
		execute_at_child(proc, env);
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
	printf("pipe read : %d | pipe write : %d\n", pipefd[0], pipefd[1]);
	setting.files = exe->files;
	setting.cmd = *exe->cmds->first;
	setting.input = exe->p_pipe;
	setting.output = pipefd[WRITE];
	if (index == 0)
		setting.input = STDIN_FILENO;
	if (!set_proc(proc, setting))
		return ;
	execute_commands(proc, exe);
	exe->p_pipe = dup(pipefd[READ]);
	printf("prev : %d\n", exe->p_pipe);
	close(pipefd[READ]);
	close(pipefd[WRITE]);
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
	execute_commands(proc, exe);
	close(exe->p_pipe);
}

void	execute_commands(t_proc *proc, t_exe *exe)
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
			execute_at_child(*proc, (const t_envp *)(*exe->env));
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
