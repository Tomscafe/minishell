/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:46:31 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:48:21 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	unsigned char	ch1;
	unsigned char	ch2;
	size_t			idx;

	idx = 0;
	while (idx < size && s1[idx])
	{
		ch1 = s1[idx];
		ch2 = s2[idx];
		if (ch1 != ch2)
		{
			return (ch1 - ch2);
		}
		idx++;
	}
	if (idx == size)
	{
		return (0);
	}
	return ((unsigned char)(s1[idx]) - (unsigned char)(s2[idx]));
}
