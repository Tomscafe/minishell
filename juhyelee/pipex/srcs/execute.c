/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 21:32:23 by juhyelee          #+#    #+#             */
/*   Updated: 2023/12/28 22:01:01 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execute_child(const t_command cmd, const char *envp[], int *pipe_fd)
{
	int		infile_fd;
	char	*file;

	infile_fd = open(cmd.infile, O_RDONLY);
	if (infile_fd == -1)
	{
		perror("Fail infile open");
		exit(EXIT_FAILURE);
	}
	file = is_accessible(cmd.f_cmd[0], envp);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (execve(file, cmd.f_cmd, (char *const *)envp) == -1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

void	execute_parent(const t_command cmd, const char *envp[], int *pipe_fd)
{
	const int	flag = O_WRONLY | O_CREAT | O_TRUNC;
	int			outfile_fd;
	char		*file;

	outfile_fd = open(cmd.outfile, flag, FILE_PERMISSION);
	if (outfile_fd == -1)
	{
		perror("Fail outfile open");
		exit(EXIT_FAILURE);
	}
	file = is_accessible(cmd.s_cmd[0], envp);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (execve(file, cmd.s_cmd, (char *const *)envp) == -1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}