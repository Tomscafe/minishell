/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hywoo <hywoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:06:56 by hywoo             #+#    #+#             */
/*   Updated: 2023/03/31 08:39:12 by hywoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_array_size(char const *s, char c)
{
	int	size;

	size = 0;
	while (*s)
	{
		if (*s != c)
			size++;
		if (!*s)
			return (size);
		while (*s != c && *s)
			s++;
		if (!*s)
			return (size);
		while (*s == c)
			s++;
	}
	return (size);
}

static void	free_res(char **res, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		free(res[i]);
		res[i] = 0;
		i++;
	}
	free(res);
}

static char	*make_res2(char const *s, char c, char *res, int i)
{
	int	size;
	int	idx;

	size = 0;
	idx = 0;
	while (s[i + size])
	{
		if (s[i + size] != c)
			size++;
		else
			break ;
	}
	res = (char *)malloc((size + 1) * sizeof(char));
	if (!res)
		return (0);
	while (idx < size)
	{
		res[idx] = s[i + idx];
		idx++;
	}
	res[idx] = 0;
	return (res);
}

static char	**make_res(char const *s, char c, char **res)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		res[k] = make_res2(s, c, res[k], i);
		if (!res[k])
		{
			free_res(res, k);
			return (0);
		}
		k++;
		while (s[i] && s[i] != c)
			i++;
	}
	res[k] = 0;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		size;
	char	**res;

	if (!s)
		return (0);
	size = ft_array_size(s, c);
	res = (char **)malloc((size + 1) * sizeof(char *));
	if (!res)
		return (0);
	res = make_res(s, c, res);
	return (res);
}
