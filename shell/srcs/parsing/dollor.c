/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:45:17 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/19 14:13:25 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dollor_len(char *str, int k, char *variable)
{
	int	len;

	len = 0;
	k++;
	while (str[k + len])
	{
		if (str[k + len] != variable[len])
			break ;
		if (str[k + len] == ' ')
			break ;
		else if (str[k + len] == '$')
			break ;
		else if (str[k + len] == '\'')
			break ;
		else if (str[k + len] == '\"')
			break ;
		else if (str[k + len] == '=')
			break ;
		len++;
	}
	if (!str[k + len])
		return (len);
	return (len);
}

int	check_dollor_opt(char *str, int *i)
{
	if (str[*i + 1] == '?')
		return (1);
	return (0);
}

char	*convert_dollor(t_envp *needle, char *str, int *i)
{
	char	*result;
	char	*temp;
	int		r;

	if (!needle)
	{
		if (check_dollor_opt(str, i))
		{
			result = ft_strdup(str);
			free (str);
			return (result);
		}
		result = remove_str(str, *i, 0, 0);
		*i = *i - 1;
		free (str);
		return (result);
	}
	else
		temp = needle->value;
	r = dollor_len(str, *i, needle->variable);
	result = remake_str(str, temp, r, i);
	*i = *i - 1;
	free (str);
	return (result);
}

int	convertable_dollor(char *str, int i)
{
	int	j;
	int	flag;

	j = 0;
	flag = 0;
	if (str[i] != '$')
		return (0);
	while (j < i)
	{
		if (str[j] == '\"')
			flag++;
		j++;
	}
	if ((flag % 2 == 0) && (!str[i + 1] || str[i + 1] == ' '))
		return (0);
	if ((flag % 2 == 1) && (str[i + 1] == '\"' || str[i + 1] == ' ' || \
		str[i + 1] == '\''))
		return (0);
	return (1);
}

char	*check_dollor(t_envp *env, char *str, int i, int flag)
{
	char	*new_str;
	t_envp	*needle;

	new_str = ft_strdup(str);
	while (new_str[i])
	{
		if (flag && new_str[i] == '\"')
			flag = 0;
		else if (!flag && new_str[i] == '\"')
			flag++;
		if (!flag && new_str[i] == '\'')
			i = ignore_quotes(new_str, i, '\'');
		if (convertable_dollor(new_str, i))
		{
			needle = find_dollor(env, new_str, i);
			new_str = convert_dollor(needle, new_str, &i);
		}
		i++;
	}
	return (new_str);
}
