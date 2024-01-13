/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:30:22 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:48:24 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*mem;
	size_t	idx;

	mem = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!mem)
	{
		return (NULL);
	}
	idx = 0;
	while (s[idx])
	{
		mem[idx] = f(idx, s[idx]);
		idx++;
	}
	mem[idx] = '\0';
	return (mem);
}
