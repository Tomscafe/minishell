/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:17:48 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/16 02:09:07 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_input(t_table table)
{
	if (table.input != STDIN_FILENO && \
		table.input != STDOUT_FILENO)
		close(table.input);
}

void	close_output(t_table table)
{
	if (table.output != STDOUT_FILENO && \
		table.output != STDIN_FILENO)
		close(table.output);
}
