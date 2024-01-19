/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:43:13 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/19 20:38:06 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*convert_st_exit(char *str, const int st_exit)
{
	const char	*str_exit = (const char *)ft_itoa(st_exit);
	char		**strs;
	char		*ret;

	if (!str_exit)
		exit(EXIT_FAILURE);
	if (!is_contain((const char *)str))
	{
		ret = ft_strdup(str);
		if (!ret)
			exit(EXIT_FAILURE);
		free((char *)str_exit);
		return (ret);
	}
	strs = ft_split(str, '$');
	if (!strs)
		exit(EXIT_FAILURE);
	ret = rejoin_strs((const char **)strs, str_exit);
	clear_strs(strs);
	free((char *)str_exit);
	return (ret);
}

int	is_contain(const char *str)
{
	size_t	index;

	index = 1;
	while (str[index])
	{
		if (str[index - 1] == '$' && str[index] == '?')
			return (1);
		index++;
	}
	return (0);
}

char	*rejoin_strs(const char **strs, const char *str_exit)
{
	size_t	index;
	size_t	size;
	char	*ret;

	size = ft_strlen(strs[0]);
	index = 1;
	while (strs[index])
	{
		size += ft_strlen(str_exit);
		size += (ft_strlen(strs[index]) - 1);
		index++;
	}
	size++;
	ret = (char *)malloc(sizeof(char) * size);
	if (!ret)
		exit(EXIT_FAILURE);
	ft_strlcpy(ret, strs[0], size);
	index = 1;
	while (strs[index])
	{
		ft_strlcat(ret, str_exit, size);
		ft_strlcat(ret, strs[index] + 1, size);
		index++;
	}
	return (ret);
}

void	heredoc_signal(int signal)
{
	signal = 1;
	printf("\n");
	exit(signal);
}
