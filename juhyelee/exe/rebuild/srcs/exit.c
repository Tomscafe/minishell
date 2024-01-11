/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:46:42 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/11 16:49:48 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_exit(const char *arg)
{
	int		exit_num;

	arg += 5;
	if (arg[0] == '\0')
		exit(0);
	exit_num = ft_atoi(arg) % 256;
	exit(exit_num);
}
