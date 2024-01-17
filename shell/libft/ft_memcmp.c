/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:33:00 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:49:27 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t size)
{
	const unsigned char	*p1 = s1;
	const unsigned char	*p2 = s2;
	size_t				idx;

	idx = 0;
	while (idx < size)
	{
		if (p1[idx] != p2[idx])
		{
			return (p1[idx] - p2[idx]);
		}
		idx++;
	}
	return (0);
}
