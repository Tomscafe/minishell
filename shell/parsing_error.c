/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hywoo <hywoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:46:09 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/14 14:46:46 by hywoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(t_token *token)
{
	t_token	*curr;

	curr = token;
	if (curr->next->type == PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	while (curr)
	{
		if (valid_redirection(curr))
			return (1);
		else if (valid_pipe(curr))
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	valid_redirection3(t_token *curr)
{
	if (!curr->next)
	{
		printf("syntax error near unexpected token `newline'\n");
		return (2);
	}
	if (curr->next->type == REDIRECTION || curr->next->type == PIPE)
	{
		printf("syntax error near unexpected token `%s'\n", curr->next->str);
		return (2);
	}
	if (!*curr->next->str)
	{
		printf("syntax error near unexpected token `newline'\n");
		return (2);
	}
	return (0);
}

int	valid_redirection2(t_token *curr)
{
	if (curr->str[0] != curr->str[1])
	{
		if (curr->next)
		{
			if (curr->next->type == REDIRECTION && curr->next->str)
			{
				if (curr->str[1] == curr->next->str[0])
				{
					printf("syntax error near unexpected token `%c%c'\n",
						curr->str[1], curr->str[1]);
					return (2);
				}
			}
		}
		printf("syntax error near unexpected token `%c'\n", curr->str[1]);
		return (2);
	}
	return (0);
}

int	valid_redirection(t_token *curr)
{
	if (curr->type != REDIRECTION)
		return (0);
	if (ft_strlen(curr->str) > 1)
	{
		if (valid_redirection2(curr))
			return (2);
	}
	if (valid_redirection3(curr))
		return (2);
	return (0);
}

int	valid_pipe(t_token *curr)
{
	int	flag;

	flag = 0;
	if (curr->type != PIPE)
		return (0);
	if (curr->next)
	{
		if (curr->next->type == PIPE)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (1);
		}
	}
	else
	{
		printf("minishell: syntax error: unexpected end of file\n");
		return (1);
	}
	return (0);
}
