/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:31:24 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:48:48 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*mem;
	size_t	len;
	size_t	idx;

	len = ft_strlen(str) + 1;
	mem = (char *)malloc(sizeof(char) * len);
	if (!mem)
	{
		return (NULL);
	}
	idx = 0;
	while (str[idx])
	{
		mem[idx] = str[idx];
		idx++;
	}
	mem[idx] = '\0';
	return (mem);
}
