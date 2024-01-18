/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:16:59 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:48:16 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	unsigned char	to_find;
	int				idx;

	to_find = ch;
	idx = ft_strlen(str);
	if (to_find == '\0')
	{
		return ((char *)(str + idx));
	}
	while (idx >= 0)
	{
		if (str[idx] == to_find)
		{
			return ((char *)(str + idx));
		}
		idx--;
	}
	return (NULL);
}
