/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:39:21 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/12 20:12:44 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	heredoc(const char *end)
{
	int		heredocfd;
	char	*input_line;

	heredocfd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!heredocfd)
		exit(EXIT_FAILURE);
	while (1)
	{
		input_line = readline("> ");
		if (input_line == NULL)
			exit(0);
		if (ft_strncmp(input_line, end, ft_strlen(input_line)) == 0)
			break ;
		ft_putendl_fd(input_line, heredocfd);
		free(input_line);
	}
	close(heredocfd);
	return (open("heredoc", O_RDONLY));
}