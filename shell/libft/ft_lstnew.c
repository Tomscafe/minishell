/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:32:57 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:49:34 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*mem;

	mem = (t_list *)malloc(sizeof(t_list));
	if (!mem)
	{
		return (NULL);
	}
	mem->content = content;
	mem->next = NULL;
	return (mem);
}
