/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:38:20 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:48:19 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_str(const char *haystack, const char *needle, size_t size);

char	*ft_strnstr(const char *haystack, const char *needle, size_t size)
{
	size_t	idx;

	if (needle[0] == '\0')
	{
		return ((char *)haystack);
	}
	idx = 0;
	while (haystack[idx] && idx < size)
	{
		if (is_str(haystack + idx, needle, size - idx))
		{
			return ((char *)(haystack + idx));
		}
		idx++;
	}
	return (NULL);
}

static int	is_str(const char *haystack, const char *needle, size_t size)
{
	char	buff;
	size_t	idx;

	idx = 0;
	while (needle[idx])
	{
		buff = haystack[idx];
		if (idx >= size)
		{
			buff = '\0';
		}
		if (buff != needle[idx])
		{
			return (0);
		}
		idx++;
	}
	return (1);
}
