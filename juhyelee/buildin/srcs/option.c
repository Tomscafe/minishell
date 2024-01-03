/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:23:17 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/03 21:43:00 by juhyelee         ###   ########.fr       */
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