/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:12:54 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:48:44 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*mem;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	mem = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!mem)
	{
		return (NULL);
	}
	ft_strlcpy(mem, s1, len_s1 + 1);
	ft_strlcat(mem, s2, len_s1 + len_s2 + 1);
	return (mem);
}
