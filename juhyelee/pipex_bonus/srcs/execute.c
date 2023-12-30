/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 09:23:29 by juhyelee          #+#    #+#             */
/*   Updated: 2023/12/30 09:52:05 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execute_command(t_list *cmd, t_proc *proc, size_t cmdidx)
{
	pid_t	child;

	child = fork();
	if (child == -1)
	{
		perror("fail to create new process");
		exit(EXIT_FAILURE);
	}
	else if (child == 0)
	{
		if (cmdidx == 0)
			execute_child(cmd, proc, proc->infd, proc->pipefd[1]);
		else if (cmdidx + 1 == (size_t)ft_lstsize(proc->clist))
			execute_child(cmd, proc, proc->prevfd, proc->outfd);
		else
			execute_child(cmd, proc, proc->prevfd, proc->pipefd[1]);
	}
	wait(NULL);
	proc->prevfd = dup(proc->pipefd[0]);
}

void	execute_child(t_list *cmd, t_proc *proc, int in, int out)
{
	char	**cmdstrs;
	char	*cmdpath;

	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(proc->infd);
	close(proc->outfd);
	close(proc->prevfd);
	close(proc->pipefd[0]);
	close(proc->pipefd[1]);
	cmdstrs = cmd->content;
	cmdpath = find_exepath(proc->path, cmdstrs[0]);
	if (execve(cmdpath, cmdstrs, proc->envp) == -1)
	{
		perror("fail to execute");
		exit(EXIT_FAILURE);
	}
}

char	*find_exepath(char **path, char *cmd)
{
	size_t	index;
	char	*exefile;

	index = 0;
	while (path[index])
	{
		exefile = merge(path[index], cmd);
		if (access(exefile, X_OK) == 0)
			return (exefile);
		index++;
	}
	perror("invalid command");
	exit(EXIT_FAILURE);
}