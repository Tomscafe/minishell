/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:17:48 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/12 13:32:54 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_input(int input)
{
	if (input != STDIN_FILENO)
		close(input);
}

void	close_output(int output)
{
	if (output != STDOUT_FILENO)
		close(output);
}
