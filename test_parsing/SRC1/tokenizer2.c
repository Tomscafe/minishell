/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hywoo <hywoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:46:18 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/14 14:46:54 by hywoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_command(t_token *token, char *str, int i, int type)
{
	int		j;
	char	*command;

	if (type == SP || type == PIPE || type == REDIRECTION)
		return (i);
	j = i;
	while (str[j] && str[j] != ' ')
	{
		type = check_type(str[j]);
		if (str[j] == '\'')
			j = ignore_quotes(str, j, '\'', 0);
		if (str[j] == '\"')
			j = ignore_quotes(str, j, '\"', 0);
		if (type == PIPE || type == REDIRECTION)
			break ;
		j++;
	}
	command = mini_strdup(str, i, j);
	add_token_back(token, command, COMMAND);
	return (j);
}

int	token_ward(t_token *token, char *str, int i, int type)
{
	int		j;
	char	*ward;

	if (type == SP || type == PIPE || type == REDIRECTION)
		return (i);
	j = i;
	while (str[j])
	{
		if (str[j] == '\'')
			j = ignore_quotes(str, j, '\'', 0);
		if (str[j] == '\"')
			j = ignore_quotes(str, j, '\"', 0);
		if (end_of_ward(str[j]))
			break ;
		j++;
	}
	ward = mini_strdup(str, i, j);
	add_token_back(token, ward, WARD);
	return (j);
}

int	token_redirection(t_token *token, char *str, int i, int type)
{
	int		j;
	char	*redirection;

	j = i;
	if (type != REDIRECTION)
		return (i);
	if (str[i + 1] == '>' || str[i + 1] == '<')
		j++;
	j++;
	redirection = mini_strdup(str, i, j);
	add_token_back(token, redirection, REDIRECTION);
	return (j);
}

int	token_pipe(t_token *token, char *str, int i, int type)
{
	int		j;
	char	*pipe;

	j = i;
	if (type != PIPE)
		return (i);
	j++;
	pipe = mini_strdup(str, i, j);
	add_token_back(token, pipe, PIPE);
	return (j);
}

int	token_flag(t_token *token)
{
	while (token->next)
		token = token->next;
	if (token->type == PIPE)
		return (1);
	else
		return (0);
}
