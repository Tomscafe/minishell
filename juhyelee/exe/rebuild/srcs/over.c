/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   over.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:35:43 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/16 19:54:59 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	apply_redirection(t_table table)
{
	dup2(table.input, STDIN_FILENO);
	close_input(table);
	dup2(table.output, STDOUT_FILENO);
	close_output(table);
	if (table.pipefd[0] != STDIN_FILENO && table.pipefd[0] != STDOUT_FILENO)
		close(table.pipefd[0]);
	if (table.pipefd[1] != STDIN_FILENO && table.pipefd[1] != STDOUT_FILENO)
		close(table.pipefd[1]);
}
