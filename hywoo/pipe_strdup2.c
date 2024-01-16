/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_strdup2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hywoo <hywoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:34:39 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/16 17:34:40 by hywoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rm_sp_strdup2(char *str, int i, int j)
{
	char	*result;
	int		space;

	space = rm_size_space(str, 0, 0, 0);
	result = malloc(sizeof(char) * (ft_strlen(str) - space + 1));
	while (str[i])
	{
		if (str[i] == '\'')
			quotes_strdup(result, str, &i, &j);
		if (str[i] == '\"')
			i++;
		result[j] = str[i];
		if (str[i] == ' ')
		{
			while (str[i] && str[i] == ' ')
				i++;
		}
		else if (str[i] == '\0')
			return (result);
		else
			i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

char	*pipe_strdup2(t_envp *env, char *str)
{
	char	*result;
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = check_dollor(env, str, 0, 0);
	if (!new_str)
	{
		result = rm_sp_strdup2(str, 0, 0);
		return (result);
	}
	result = rm_sp_strdup2(new_str, 0, 0);
	free (new_str);
	return (result);
}
