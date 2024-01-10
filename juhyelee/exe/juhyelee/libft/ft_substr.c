/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:39:40 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:48:08 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size(char const *s, unsigned int start, size_t len);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*mem;
	size_t	size;
	size_t	idx;

	size = get_size(s, start, len);
	mem = (char *)malloc(sizeof(char) * (size + 1));
	if (!mem)
	{
		return (NULL);
	}
	idx = 0;
	while (idx < size)
	{
		mem[idx] = s[idx + start];
		idx++;
	}
	mem[idx] = '\0';
	return (mem);
}

static size_t	get_size(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		return (0);
	}
	else if (start + len >= s_len)
	{
		return (s_len - start);
	}
	return (len);
}
