/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:16:48 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/11 16:35:15 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_pwd(void)
{
	char	buffer[2024];
	char	*ret;

	ret = getcwd(buffer, 2024);
	if (!ret)
		return (EXIT_FAILURE);
	free(ret);
	ft_putendl_fd(buffer, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
