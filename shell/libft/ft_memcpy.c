/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:56:41 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:49:25 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	const unsigned char	*s_arr = src;
	unsigned char		*d_arr;
	size_t				idx;

	if (!src && !dst)
	{
		return (NULL);
	}
	d_arr = dst;
	idx = 0;
	while (idx < len)
	{
		d_arr[idx] = s_arr[idx];
		idx++;
	}
	return (dst);
}
