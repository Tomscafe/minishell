/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 21:05:31 by juhyelee          #+#    #+#             */
/*   Updated: 2023/12/28 21:55:50 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_command	cmd;
	pid_t		child;
	int			pipe_fd[2];

	parse(argc, (const char **)argv, &cmd);
	if (pipe(pipe_fd) == -1)
	{
		perror("Fail pipe");
		exit(1);
	}
	child = fork();
	if (child == -1)
	{
		perror("Fail fork");
		exit(1);
	}
	if (child == 0)
		execute_child(cmd, (const char **)envp, pipe_fd);
	if (waitpid(child, NULL, WUNTRACED) == -1)
	{
		perror("Fail wait");
		exit(EXIT_FAILURE);
	}
	execute_parent(cmd, (const char **)envp, pipe_fd);
	return (0);
}