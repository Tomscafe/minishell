/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:39:21 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/11 18:42:42 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	heredoc(const char *end)
{
	int		heredoc;
	char	*inputline;

	heredoc = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!heredoc)
		exit(EXIT_FAILURE);
	while (1)
	{
		inputline = readline("> ");
		if (ft_strncmp(inputline, end, ft_strlen(inputline)) == 0)
		{
			free(inputline);
			break ;
		}
		ft_putendl_fd(inputline, heredoc);
		free(inputline);
	}
	return (heredoc);
}
