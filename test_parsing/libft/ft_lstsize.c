/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:19:30 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:49:32 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*p;
	int		size;

	size = 0;
	p = lst;
	while (p)
	{
		size++;
		p = p->next;
	}
	return (size);
}
