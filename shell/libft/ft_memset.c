/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:30:25 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:49:16 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int ch, size_t len)
{
	unsigned char	*arr;
	size_t			idx;

	arr = str;
	idx = 0;
	while (idx < len)
	{
		arr[idx] = ch;
		idx++;
	}
	return (str);
}
