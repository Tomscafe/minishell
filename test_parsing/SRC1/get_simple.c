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

void	cutting_filename(t_envp *env, t_redirection *rd, char *file)
{
	char	*org_name;
	char	*edt_name;
	int		size;
	int		j;

	j = 0;
	j = ignore_space(file, 0, SP);
	size = file_name_length(file, 0);
	org_name = malloc(sizeof(char) * (size + 1));
	get_copy_filename(org_name, file, j, size);
	if (!check_heredoc(rd->symbol))
	{
		edt_name = pipe_strdup(env, org_name);
		if (!*edt_name)
			rd->non=org_name;
		else
			free (org_name);
		free (file);
		rd->file = edt_name;
		printf("orgname:%s\n",rd->non);
	}
	else
	{
		free (file);
		rd->file = org_name;
	}
}

void	get_simple_ward(t_envp *env, t_simple *simple, char *ward)
{
	char	*tmp;
	char	*tmp2;
	char	*result;
	char	split_char[2];

	tmp = pipe_strdup(env, ward);
	split_char[0] = -1;
	split_char[1] = 0;
	if (!*tmp)
		free (tmp);
	else if (!simple->ward)
		simple->ward = tmp;
	else
	{
		tmp2 = ft_strjoin(split_char, tmp);
		result = ft_strjoin(simple->ward, tmp2);
		free (simple->ward);
		free (tmp);
		free (tmp2);
		simple->ward = result;
	}
}

void	get_ward(t_envp *env, t_simple *simple, char *file)
{
	int	i;

	i = ignore_space(file, 0, SP);
	i += file_name_length(file, i);
	i = ignore_space(file, i, SP);
	get_command_ward(env, simple, file, i);
}

void	get_simple(t_envp *env, t_simple *simple, t_redirection *rd)
{
	int	flag_com;

	if (!simple->command)
		flag_com = 0;
	else
		flag_com = 1;
	while (rd)
	{
		if (!flag_com && have_others(rd->file))
		{
			flag_com++;
			get_command(env, simple, rd->file);
			cutting_filename(env, rd, rd->file);
		}
		else if (flag_com && have_others(rd->file))
		{
			get_ward(env, simple, rd->file);
			cutting_filename(env, rd, rd->file);
		}
		else if (!have_others(rd->file))
			cutting_filename(env, rd, rd->file);
		rd = rd->next;
	}
}
