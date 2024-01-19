/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hywoo <hywoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:46:19 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/14 14:46:22 by hywoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ignore_space(char *str, int i, int type)
{
	if (type != SP)
		return (i);
	while (str[i] == ' ')
		i++;
	return (i);
}

int	ignore_quotes(char *str, int j, char c, int syntax)
{
	int	invalid;

	invalid = -1;
	if (str[j] != c)
		return (j);
	if (str[j] == c)
		j++;
	while (str[j] && str[j] != c)
		j++;
	if (str[j] == c)
		return (j);
	if (!syntax)
		return (j);
	else
		return (invalid);
}

int	check_type(char c)
{
	if (c == '\'')
		return (QUOTE);
	if (c == '\"')
		return (QUOTES);
	if (c == '>' || c == '<')
		return (REDIRECTION);
	if (c == '|')
		return (PIPE);
	if (c == ' ')
		return (SP);
	return (WARD);
}

int	valid_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i = ignore_quotes(str, i, str[i], 1);
			if (i == -1)
			{
				printf("minishell: syntax error\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	end_of_ward(char c)
{
	int	type;

	type = check_type(c);
	if (type == REDIRECTION)
		return (1);
	if (type == PIPE)
		return (1);
	return (0);
}
