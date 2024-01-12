/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:17:48 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/12 19:25:20 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_input(int input, int intdef)
{
	if (input != intdef)
		close(input);
}

void	close_output(int output, int outdef)
{
	if (output != outdef)
		close(output);
}
