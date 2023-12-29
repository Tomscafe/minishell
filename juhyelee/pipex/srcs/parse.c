/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 21:05:41 by juhyelee          #+#    #+#             */
/*   Updated: 2023/12/28 23:07:32 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	parse(const size_t argc, const char *argv[], t_command *cmd)
{
	if (argc != 5)
	{
		perror("The number of arguments must be 4");
		exit(EXIT_FAILURE);
	}
	cmd->infile = (char *)argv[1];
	cmd->f_cmd = ft_split(argv[2], ' ');
	cmd->s_cmd = ft_split(argv[3], ' ');
	cmd->outfile = (char *)argv[4];
}

void	clear_path(char **path)
{
	size_t	index;

	index = 0;
	while (path[index])
	{
		free(path[index]);
		index++;
	}
	free(path[index]);
	free(path);
}


char	**find_path(const char *envp[])
{
	char	**path;
	size_t	index;

	path = NULL;
	index = 0;
	while (envp[index])
	{
		if (ft_strncmp("PATH", envp[index], 4) == 0)
		{
			path = ft_split(envp[index] + 5, ':'); // skip "PATH="
			break ;
		}
		index++;
	}
	return (path);
}

char	*is_accessible(const char *cmd, const char *envp[])
{
	size_t		index;
	char		*cmd_path;
	const char	**path = (const char **)find_path(envp);

	if (!path)
	{
		perror("Not found path");
		exit(EXIT_FAILURE);
	}
	index = 0;
	while (path[index])
	{
		cmd_path = get_cmd_path(path[index], cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			clear_path((char **)path);
			return (cmd_path);
		}
		index++;
	}
	perror("Invalid command");
	exit(EXIT_FAILURE);
}

char	*get_cmd_path(const char *path, const char *cmd)
{
	char			*cmd_path;
	const size_t	path_len = ft_strlen(path);
	const size_t	cmd_len = ft_strlen(cmd);

	cmd_path = (char *)malloc(sizeof(char) * (path_len + cmd_len + 2)); // '/' and null char
	if (!cmd_path)
	{
		perror("Fail malloc");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(cmd_path, path, path_len + 1);
	ft_strlcpy(cmd_path + path_len, "/", 2);
	ft_strlcpy(cmd_path + path_len + 1, cmd, cmd_len + 1);
	return (cmd_path);
}