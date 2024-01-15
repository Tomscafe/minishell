/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_strdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hywoo <hywoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:46:11 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/14 14:46:47 by hywoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rm_size_space(char *str, int i, int space, int cnt)
{
	while (str[i])
	{
		if (str[i] == '\'')
			i = ignore_quotes(str, i, '\'');
		if (str[i] == '\"')
			i = ignore_quotes(str, i, '\"');
		if (str[i] == ' ')
		{
			while (str[i] && str[i] == ' ')
			{
				i++;
				space++;
			}
			cnt++;
		}
		i++;
	}
	return (space - cnt);
}

void	quotes_strdup(char *result, char *str, int *i, int *j)
{
	char	c;

	c = str[*i];
	while (str[*i])
	{
		result[*j] = str[*i];
		*i += 1;
		*j += 1;
		if (str[*i] == c)
		{
			result[*j] = str[*i];
			*i += 1;
			*j += 1;
			break ;
		}
	}
}

char	*rm_sp_strdup(char *str, int i, int j)
{
	char	*result;
	int		space;

	space = rm_size_space(str, 0, 0, 0);
	result = malloc(sizeof(char) * (ft_strlen(str) - space + 1));
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			quotes_strdup(result, str, &i, &j);
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

char	*pipe_strdup(t_envp *env, char *str)
{
	char	*result;
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = check_dollor(env, str, 0, 0);
	if (!new_str)
	{
		result = rm_sp_strdup(str, 0, 0);
		return (result);
	}
	result = rm_sp_strdup(new_str, 0, 0);
	free (new_str);
	return (result);
}