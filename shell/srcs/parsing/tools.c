/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:46:19 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/17 22:55:58 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ignore_space(char *str, int i, int type)
{
	if (type != SP)
		return (i);
	while (str[i] == ' ')
		i++;
	return (i);
}

int	ignore_quotes(char *str, int j, char c)
{
	if (str[j] != c)
		return (j);
	if (str[j] == c)
		j++;
	while (str[j] && str[j] != c)
		j++;
	return (j);
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
	int	flag1;
	int	flag2;

	i = 0;
	flag1 = 0;
	flag2 = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			flag1++;
		if (str[i] == '\"')
			flag2++;
		i++;
	}
	if (flag1 % 2 || flag2 % 2)
	{
		printf("minishell: syntax error\n");
		return (1);
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
