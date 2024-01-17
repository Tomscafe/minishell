/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:26:51 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:49:30 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int ch, size_t len)
{
	const unsigned char	*arr = str;
	unsigned char		to_find;
	size_t				idx;

	to_find = ch;
	idx = 0;
	while (idx < len)
	{
		if (arr[idx] == to_find)
		{
			return ((void *)(arr + idx));
		}
		idx++;
	}
	return (NULL);
}
