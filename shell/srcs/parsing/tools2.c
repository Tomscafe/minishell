/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:16:09 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/17 22:56:00 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_copy_filename(char *str, char *file, int j, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		str[i] = file[j];
		i++;
		j++;
	}
	str[i] = '\0';
}

int	check_heredoc(char *str)
{
	char	c;

	if (str[0] == '<' || str[0] == '>')
	{
		c = str[0];
		if (str[1] == c)
			return (1);
	}
	return (0);
}

void	add_split_char(char *result, int *i, int *j)
{
	result[*j] = -1;
	*i += 1;
	*j += 1;
}

int	have_others(char *file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		i = ignore_quotes(file, i, '\'', 0);
		i = ignore_quotes(file, i, '\"', 0);
		if (file[i] == ' ')
		{
			i = ignore_space(file, i, SP);
			if (file[i])
				return (1);
		}
		i++;
	}
	return (0);
}

int	file_name_length(char *file, int j)
{
	int	size;

	size = j;
	j = ignore_space(file, j, SP);
	while (file[j] && file[j] != ' ')
	{
		j = ignore_quotes(file, j, '\'', 0);
		j = ignore_quotes(file, j, '\"', 0);
		j++;
	}
	size = j - size;
	return (size);
}
