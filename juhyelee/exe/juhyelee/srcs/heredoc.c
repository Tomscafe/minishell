/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:34:40 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/10 18:33:45 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	heredoc(const char *end_point)
{
	char	*input_line;
	int		heredoc_fd;

	heredoc_fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd == -1)
	{
		fprintf(stderr, "here doc: fail open\n");
		return (-1);
	}
	while (1)
	{
		input_line = readline("> ");
		if (input_line == NULL)
			return (-1);
		if (ft_strncmp(end_point, input_line, ft_strlen(input_line)) == 0)
			break ;
		ft_putendl_fd(input_line, heredoc_fd);
		free(input_line);
	}
	return (heredoc_fd);
}

char	*is_executable(const t_table table)
{
	char		*path;
	size_t		index;
	struct stat	protection;
	int			mode;

	index = 0;
	while (table.env[index])
	{
		path = ft_strjoin(table.env[index], "/");
		path = ft_strjoin(path, table.command);
		if (stat(path, &protection) == -1)
		{
			fprintf(stderr, "is executable: stat error\n");
			return (NULL);
		}
		mode = protection.st_mode & 0777;
		if (((mode >> 6) & 1) && ((mode >> 3) & 1) && (mode & 1))
			return (path);
		index++;
	}
	return (NULL);
}
