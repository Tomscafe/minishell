/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:23:17 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/04 09:56:05 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buildin.h"

int	check_echo_option(const char *option)
{
	if (ft_strlen(option) != 2)
		return (1);
	else if (option[0] != '-')
		return (1);
	else if (option[1] != 'n')
		return (1);
	return (0);
}

int	check_option(const char *option)
{
	if (ft_strlen(option) != 2)
		return (1);
	else if (option[0] != '-')
		return (1);
	return (0);
}

void	clear_strs(char **strs)
{
	size_t	index;

	index = 0;
	while (strs[index])
	{
		free(strs[index]);
		index++;
	}
	free(strs[index]);
	free(strs);
}

void	print_error(const char *cmd, const char *message, const char *arg)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: %s: %s\n", cmd, arg, message);
}
