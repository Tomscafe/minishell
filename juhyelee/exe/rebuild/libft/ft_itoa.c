/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 17:52:15 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:49:56 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_len(long long n);
static char		*get_res(long long n, size_t len);

char	*ft_itoa(int n)
{
	return (get_res(n, get_len(n)));
}

static size_t	get_len(long long n)
{
	size_t		len;

	len = 0;
	if (n == 0)
	{
		return (1);
	}
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*get_res(long long n, size_t len)
{
	char	*mem;
	int		idx;

	mem = (char *)malloc(sizeof(char) * (len + 1));
	if (!mem)
		return (NULL);
	mem[len] = '\0';
	if (n == 0)
		mem[0] = '0';
	else
	{
		if (n < 0)
		{
			mem[0] = '-';
			n *= -1;
		}
		idx = len - 1;
		while (n != 0)
		{
			mem[idx] = n % 10 + '0';
			n /= 10;
			idx--;
		}
	}
	return (mem);
}
