/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:54:36 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/04 12:36:53 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/here_doc.h"

int	contain_new_line(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*input(int fd)
{
	static char	*remain;
	char		*line;
	char		buffer[BUFFER_SIZE];
	int			buffer_size;

	while (1)
	{
		buffer_size = read(fd, buffer, BUFFER_SIZE);
		if (buffer_size == -1)
			break ;
		if (buffer_size == 0)
			return (remain);
		if (contain_new_line(buffer))
		{
			line = merge(remain, buffer, get_line_size(buffer));
			free(remain);
			remain = NULL;
			return (line);
		}
		remain = merge(remain, buffer, BUFFER_SIZE);
	}
	return (check_remain(remain));
}

char	*merge(char *s1, char *s2, size_t s2_len)
{
	char	*ret;
	size_t	ret_size;

	if (!s1)
	{
		ret_size = s2_len + 1;
		ret = (char *)malloc(sizeof(char) * ret_size);
		if (ret)
			ft_strlcpy(ret, s2, s2_len + 1);
		return (ret);
	}
	ret_size = ft_strlen(s1) + s2_len + 1;
	ret = (char *)malloc(sizeof(char) * ret_size);
	if (ret)
	{
		ft_strlcpy(ret, s1, ret_size);
		ft_strlcat(ret, s2, ret_size);
	}
	return (ret);
}

char	*check_remain(char *remain)
{
	if (remain)
	{
		free(remain);
		remain = NULL;
	}
	return (remain);
}

size_t	get_line_size(char *str)
{
	size_t	size;

	size = 0;
	while (*str)
	{
		if (*str == '\n')
			return (size);
		str++;
		size++;
	}
	return (0);
}
