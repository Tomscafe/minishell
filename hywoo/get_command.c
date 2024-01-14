/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hywoo <hywoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:46:00 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/14 14:46:31 by hywoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	have_others(char *file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		i = ignore_quotes(file, i, '\'');
		i = ignore_quotes(file, i, '\"');
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

int	file_name_lenth(char *file, int i)
{
	while (file[i] && file[i] != ' ')
	{
		i = ignore_quotes(file, i, '\'');
		i = ignore_quotes(file, i, '\"');
		i++;
	}
	return (i);
}

void	cutting_filename(t_redirection *rd, char *file)
{
	char	*first_file;
	int		size;
	int		i;

	i = 0;
	size = file_name_lenth(file, 0);
	first_file = malloc(sizeof(char) * (size + 1));
	while (i < size)
	{
		first_file[i] = file[i];
		i++;
	}
	first_file[i] = '\0';
	free (file);
	rd->file = first_file;
}

void	get_command_ward(t_simple *simple, char *file, int j)
{
	char	*ward;
	int		r;
	int		size;

	r = 0;
	size = ft_strlen(file);
	ward = malloc(sizeof(char) * (size - j + 1));
	while (j < size)
	{
		ward[r] = file[j];
		j++;
		r++;
	}
	ward[r] = '\0';
	simple->ward = ward;
}

void	get_command(t_simple *simple, char *file, int i, int j)
{
	char	*com;
	int		r;

	i = file_name_lenth(file, 0);
	j = file_name_lenth(file, i + 1);
	com = malloc(sizeof(char) * (j - i + 1));
	r = 0;
	while (i + 1 < j)
	{
		com[r] = file[i + 1];
		i++;
		r++;
	}
	com[r] = '\0';
	simple->command = com;
	if (file[j] == ' ')
		j++;
	if (ft_strlen(file) > j)
		get_command_ward(simple, file, j);
}
