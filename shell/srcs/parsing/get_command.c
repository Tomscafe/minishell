/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:46:00 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/17 22:55:29 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_simple	*make_simple_command(t_token *front)
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
		simple->command = pipe_strdup(front->env, front->str);
	else
		return (simple);
	if (front->next)
	{
		if (front->next->type == WARD)
			simple->ward = pipe_strdup(front->env, front->next->str);
	}
	return (simple);
}

void	get_command_ward(t_envp *env, t_simple *simple, char *file, int j)
{
	char	*ward;
	int		i;
	int		size;

	i = 0;
	ward = NULL;
	while (file[j])
	{
		j = ignore_space(file, j, SP);
		if (ward)
		{
			i = ft_strlen(ward);
			free (ward);
		}
		size = file_name_length(file, j);
		ward = malloc(sizeof(char) * (size + 1));
		get_copy_filename(ward, file, j, size);
		get_simple_ward(env, simple, ward);
		j += size;
		j = ignore_space(file, j, SP);
	}
}

void	get_command(t_envp *env, t_simple *simple, char *file)
{
	char	*com;
	int		j;
	int		size;

	j = 0;
	j = ignore_space(file, j, SP);
	j = file_name_length(file, 0);
	j = ignore_space(file, j, SP);
	size = file_name_length(file, j);
	com = malloc(sizeof(char) * (size + 1));
	get_copy_filename(com, file, j, size);
	simple->command = pipe_strdup(env, com);
	free (com);
	j += size;
	if (file[j] == ' ')
		j = ignore_space(file, j, SP);
	if (file[j])
		get_command_ward(env, simple, file, j);
}
