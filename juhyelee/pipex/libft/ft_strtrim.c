/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:52:20 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:48:11 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(const char ch, char const *set);
static int	get_end(const char *s1, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*mem;
	int		start;
	int		len;

	start = 0;
	while (is_set(s1[start], set) && s1[start])
	{
		start++;
	}
	len = get_end(s1, set) - start + 1;
	if (len < 0)
	{
		mem = (char *)malloc(sizeof(char));
		mem[0] = '\0';
		return (mem);
	}
	return (ft_substr(s1, start, len));
}

static int	is_set(const char ch, char const *set)
{
	size_t	idx;

	idx = 0;
	while (set[idx])
	{
		if (ch == set[idx])
		{
			return (1);
		}
		idx++;
	}
	return (0);
}

static int	get_end(const char *s1, char const *set)
{
	int	end;

	end = ft_strlen(s1) - 1;
	if (end < 0)
	{
		end = 0;
	}
	while (is_set(s1[end], set) && end >= 0)
	{
		end--;
	}
	return (end);
}
