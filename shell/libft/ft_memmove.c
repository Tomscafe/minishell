/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:04:16 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:49:18 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	move(char *dst, const char *src, int len);

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!dst && !src)
	{
		return (NULL);
	}
	move(dst, src, len);
	return (dst);
}

static void	move(char *dst, const char *src, int len)
{
	int	idx;

	if (src < dst)
	{
		idx = len - 1;
		while (idx >= 0)
		{
			dst[idx] = src[idx];
			idx--;
		}
	}
	else
	{
		idx = 0;
		while (idx < len)
		{
			dst[idx] = src[idx];
			idx++;
		}
	}
}
