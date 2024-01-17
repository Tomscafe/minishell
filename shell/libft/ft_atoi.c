/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:43:30 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:50:29 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_result(const char *str);

int	ft_atoi(const char *str)
{
	int		sign;

	while ((*str >= 9 && *str <= 13) || *str == 32)
	{
		str++;
	}
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			sign *= -1;
		}
		str++;
	}
	return (sign * get_result(str));
}

static int	get_result(const char *str)
{
	int		result;

	result = 0;
	while (ft_isdigit(*str))
	{
		result = (*str - '0') + (result * 10);
		str++;
	}
	return (result);
}
