/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 21:05:28 by juhyelee          #+#    #+#             */
/*   Updated: 2023/12/30 09:57:36 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_proc
{
	int		infd;
	int		outfd;
	int		prevfd;
	int		pipefd[2];
	char	**path;
	char	**envp;
	t_list	*clist;
}t_proc;

void	set_proc(int argc, char *argv[], char *envp[], t_proc *proc);
void	set_commands(int argc, char *argv[], t_list **clist);
char	**set_path(char *envp[]);

void	execute_command(t_list *cmd, t_proc *proc, size_t cmdidx);
void	execute_child(t_list *cmd, t_proc *proc, int in, int out);

char	*find_exepath(char **path, char *cmd);
char	*merge(char *s1, char *s2);

void	clear_proc(t_proc *proc);
void	clear_strs(void *arg);

#endif