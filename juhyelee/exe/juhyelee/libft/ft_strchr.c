/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:07:22 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:48:51 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	unsigned char	buff;
	size_t			idx;

	idx = 0;
	buff = ch;
	while (str[idx])
	{
		if (str[idx] == buff)
		{
			return ((char *)(str + idx));
		}
		idx++;
	}
	if (buff == '\0')
	{
		return ((char *)(str + idx));
	}
	return (NULL);
}
