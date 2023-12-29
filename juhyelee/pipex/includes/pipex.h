/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 21:05:28 by juhyelee          #+#    #+#             */
/*   Updated: 2023/12/28 21:42:25 by juhyelee         ###   ########.fr       */
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
# define FILE_PERMISSION 0644

typedef struct s_command
{
	char	**f_cmd;
	char	**s_cmd;
	char	*infile;
	char	*outfile;
}t_command;

void	parse(const size_t argc, const char *argv[], t_command *cmd);

void	clear_path(char **path);
char	**find_path(const char *envp[]);
char	*is_accessible(const char *cmd, const char *envp[]);
char	*get_cmd_path(const char *path, const char *cmd);

void	execute_child(const t_command cmd, const char *envp[], int *pipe_fd);
void	execute_parent(const t_command cmd, const char *envp[], int *pipe_fd);

#endif