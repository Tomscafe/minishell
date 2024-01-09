/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:59:54 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/04 14:48:24 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/here_doc.h"

void	heredoc(const char *end_str, const int output)
{
	char	*input_line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input_line = readline("> ");
		if (input_line == NULL)
			exit(0);
		if (ft_strncmp(input_line, end_str, ft_strlen(input_line)) == 0)
			break ;
		ft_putendl_fd(input_line, output);
		free(input_line);
	}
}
