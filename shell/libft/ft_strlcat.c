/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:32:33 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:48:42 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t d_size)
{
	size_t	d_len;
	size_t	s_len;
	size_t	d_idx;
	size_t	s_idx;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	if (d_size <= d_len)
	{
		return (s_len + d_size);
	}
	d_idx = d_len;
	s_idx = 0;
	while (d_idx + 1 < d_size && src[s_idx])
	{
		dst[d_idx] = src[s_idx];
		d_idx++;
		s_idx++;
	}
	dst[d_idx] = '\0';
	return (s_len + d_len);
}
