/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:44:24 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/17 20:07:22 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (pipe(proc->pipefd) < 0)
		exit(EXIT_FAILURE);
	if (!set_proc(proc, (const t_exe *)exe, index))
		return ;
	execute_commands(proc, exe);
}

void	last_command(t_proc *proc, t_exe *exe)
{
	if (!set_proc(proc, exe, exe->n_cmd - 1))
		return ;
	execute_commands(proc, exe);
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
