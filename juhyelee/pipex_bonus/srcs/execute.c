/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 09:23:29 by juhyelee          #+#    #+#             */
/*   Updated: 2023/12/30 10:22:40 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execute_command(t_list *cmd, t_proc *proc, size_t cmdidx)
{
	pid_t	child;

	pipe(proc->pipefd);
	if (proc->prevfd != -1)
		dup2(proc->prevfd, proc->pipefd[0]);
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
	close(proc->pipefd[0]);
	close(proc->pipefd[1]);
}

void	execute_child(t_list *cmd, t_proc *proc, int in, int out)
{
	char	**cmdstrs;
	char	*cmdpath;

	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	puts("here");
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
	exit(EXIT_SUCCESS);
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

char	*merge(char *s1, char *s2)
{
	int		size;
	char	*ret;

	size = ft_strlen(s1) + ft_strlen(s2) + 2;
	ret = (char *)malloc(sizeof(char) * size);
	if (!ret)
	{
		perror("fail to merge");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(ret, s1, size);
	ft_strlcat(ret, "/", size);
	ft_strlcat(ret, s2, size);
	return (ret);
}

void	clear_strs(void *arg)
{
	char	**strs;
	size_t	index;

	strs = arg;
	index = 0;
	while (strs[index])
	{
		free(strs[index]);
		index++;
	}
	free(strs[index]);
	free(strs);
}