/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollor2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:45:24 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/17 22:55:17 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envp	*find_dollor(t_envp *needle, char *str, int i)
{
	int	k;

	i++;
	while (needle)
	{
		k = 0;
		while (needle->variable[k]
			&& needle->variable[k] == str[i + k])
			k++;
		if (!needle->variable[k] && (str[i + k] == ' '
				|| str[i + k] == '\'' || str[i + k] == '\"'
				|| str[i + k] == '$' || str[i + k] == '\0'))
			return (needle);
		needle = needle->next;
	}
	return (NULL);
}

void	remake_str2(char *result, char *temp, int *k, int *t)
{
	while (temp[*t])
	{
		result[*k + *t] = temp[*t];
		*t += 1;
	}
	*k += *t;
}

char	*remake_str(char *str, char *temp, int r, int *i)
{
	char	*result;
	int		k;
	int		j;
	int		t;

	k = 0;
	j = 0;
	t = 0;
	result = malloc(sizeof(char)
			* (ft_strlen(str) - r + ft_strlen(temp) + 1));
	while (str[j])
	{
		if (j == *i)
		{
			remake_str2(result, temp, &k, &t);
			j += r + 1;
			t = j;
		}
		result[k] = str[j];
		k++;
		j++;
	}
	result[k] = '\0';
	*i = t;
	return (result);
}

char	*remove_str(char *str, int i, int j, int t)
{
	int		rm_size;
	char	*result;

	rm_size = 1;
	while (str[i + rm_size])
	{
		if (str[i + rm_size] == ' ' || str[i + rm_size] == '$'
			|| str[i + rm_size] == '\'' || str[i + rm_size] == '\"')
			break ;
		rm_size++;
	}
	result = malloc(sizeof(char) * (ft_strlen(str) - rm_size + 1));
	while (str[t])
	{
		if (t == i)
			t += rm_size;
		result[j] = str[t];
		j++;
		t++;
	}
	result[j] = '\0';
	return (result);
}
