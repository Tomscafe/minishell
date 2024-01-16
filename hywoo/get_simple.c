/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_simple.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hywoo <hywoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:46:03 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/14 14:46:37 by hywoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_simple	*make_simple_command(t_token *front, t_command *com)
{
	t_simple	*simple;

	simple = malloc(sizeof(t_simple));
	if (!simple)
		exit (-1);
	if (!front)
		return (simple);
	simple->command = NULL;
	simple->ward = NULL;
	if (front->type == COMMAND || front->type == WARD)
		simple->command = pipe_strdup2(front->env, front->str);
	else
		return (simple);
	if (front->next)
	{
		if (front->next->type == WARD)
			simple->ward = pipe_strdup(front->env, front->next->str);
	}
	return (simple);
}

void	get_add_back_ward(t_simple *simple, char *file, int i, int j)
{
	char	*ward;
	int		r;

	ward = malloc(sizeof(char) * (ft_strlen(simple->ward) + j - i + 1));
	r = 0;
	while (simple->ward[r])
	{
		ward[r] = simple->ward[r];
		r++;
	}
	while (i + 1 < j)
	{
		ward[r] = file[i + 1];
		r++;
		i++;
	}
	ward[r] = '\0';
	free (simple->ward);
	simple->ward = ward;
}

void	get_add_new_ward(t_simple *simple, char *file, int i, int j)
{
	char	*ward;
	int		r;

	ward = malloc(sizeof(char) * (j - i + 1));
	r = 0;
	while (i + 1 < j)
	{
		ward[r] = file[i + 1];
		i++;
		r++;
	}
	ward[r] = '\0';
	simple->ward = ward;
}

void	get_ward(t_simple *simple, char *file)
{
	char	*ward;
	int		i;
	int		j;

	i = file_name_lenth(file, 0);
	j = ft_strlen(file);
	if (simple->ward)
		get_add_back_ward(simple, file, i, j);
	else
		get_add_new_ward(simple, file, i, j);
}

void	get_simple(t_simple *simple, t_redirection *rd)
{
	int	flag;

	if (!simple->command)
		flag = 0;
	else
		flag = 1;
	while (rd)
	{
		if (!flag && have_others(rd->file))
		{
			flag++;
			get_command(simple, rd->file, 0, 0);
			cutting_filename(rd, rd->file);
		}
		else if (flag && have_others(rd->file))
		{
			get_ward(simple, rd->file);
			cutting_filename(rd, rd->file);
		}
		rd = rd->next;
	}
}
