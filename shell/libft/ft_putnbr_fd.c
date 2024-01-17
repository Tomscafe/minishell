/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <griiim134@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:18:36 by juhyelee          #+#    #+#             */
/*   Updated: 2023/03/20 16:48:57 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put_to_file(long long n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	long long	buff;

	buff = n;
	if (buff < 0)
	{
		write(fd, "-", 1);
		buff *= -1;
	}
	put_to_file(buff, fd);
}

static void	put_to_file(long long n, int fd)
{
	if (n < 10)
	{
		n += '0';
		write(fd, &n, 1);
		return ;
	}
	put_to_file(n / 10, fd);
	put_to_file(n % 10, fd);
}
