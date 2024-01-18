/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:18:30 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:48:53 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**clean_mem(char **mem, int idx);
static size_t	get_size(char const *s, const char c);
static size_t	get_len(char const *s, const char c);
static size_t	jump(char const *s, const char c);

char	**ft_split(char const *s, char c)
{
	char	**mem;
	size_t	size;
	size_t	len;
	size_t	idx;

	size = get_size(s, c);
	mem = (char **)malloc(sizeof(char *) * (size + 1));
	if (!mem)
		return (NULL);
	idx = 0;
	while (idx < size && *s)
	{
		s += jump(s, c);
		len = get_len(s, c);
		mem[idx] = (char *)malloc(sizeof(char) * (len + 1));
		if (!mem[idx])
			return (clean_mem(mem, idx));
		ft_strlcpy(mem[idx], s, len + 1);
		len += jump(s, c);
		s += len;
		idx++;
	}
	mem[idx] = NULL;
	return (mem);
}

static char	**clean_mem(char **mem, int idx)
{
	while (idx >= 0)
	{
		free(mem[idx]);
		idx--;
	}
	free(mem);
	return (NULL);
}

static size_t	get_size(char const *s, const char c)
{
	size_t	idx;
	size_t	size;

	if (s[0] == '\0')
		return (0);
	if (s[1] == '\0')
	{
		if (s[0] == c)
			return (0);
		return (1);
	}
	idx = 1;
	size = 0;
	while (s[idx])
	{
		if (s[idx - 1] != c && s[idx] == c)
			size++;
		idx++;
	}
	if (s[idx - 1] != c)
		size++;
	return (size);
}

static size_t	get_len(const char *s, const char c)
{
	size_t	len;

	len = 0;
	while (s[len] != c && s[len])
	{
		len++;
	}
	return (len);
}

static size_t	jump(const char *s, const char c)
{
	size_t	idx;

	idx = 0;
	while (s[idx] == c && s[idx])
	{
		idx++;
	}
	return (idx);
}
