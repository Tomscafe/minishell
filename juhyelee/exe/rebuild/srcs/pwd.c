/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:16:48 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/13 13:50:43 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_pwd(const t_table table)
{
	pid_t	child;
	int		exit_num;
	char	buffer[2024];
	char	*ret;

	child = fork();
	if (child < 0)
		exit(EXIT_FAILURE);
	else if (child == 0)
	{
		builtin_output(table.input, table.output);
		ret = getcwd(buffer, 2024);
		if (!ret)
			return (EXIT_FAILURE);
		ft_putendl_fd(buffer, STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	waitpid(child, &exit_num, 0);
	return (WEXITSTATUS(exit_num));
}
