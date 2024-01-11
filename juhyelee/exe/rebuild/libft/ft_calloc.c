/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:05:36 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:50:23 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	size_t	len;
	size_t	idx;

	len = count * size;
	mem = (char *)malloc(sizeof(char) * len);
	if (!mem)
	{
		return (NULL);
	}
	idx = 0;
	while (idx < len)
	{
		mem[idx] = 0;
		idx++;
	}
	return (mem);
}
