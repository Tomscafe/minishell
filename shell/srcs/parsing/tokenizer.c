/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:46:16 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/17 22:55:53 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*init_token(t_token *token)
{
	token = malloc(sizeof(t_token));
	if (!token)
		exit (-1);
	token->str = NULL;
	token->type = 0;
	token->next = NULL;
	token->env = NULL;
	return (token);
}

void	add_token_back(t_token *token, char *str, int type)
{
	t_token	*new;

	new = init_token(NULL);
	new->str = str;
	new->type = type;
	new->env = token->env;
	while (token->next)
		token = token->next;
	token->next = new;
}

void	tokenizer(t_token *token, char *str)
{
	int	i;
	int	type;
	int	flag;

	i = 0;
	flag = 1;
	while (str[i])
	{
		i = ignore_space(str, i, check_type(str[i]));
		type = check_type(str[i]);
		if (flag)
			i = token_command(token, str, i, type);
		else
			i = token_ward(token, str, i, type);
		type = check_type(str[i]);
		i = token_redirection(token, str, i, type);
		i = token_pipe(token, str, i, type);
		flag = token_flag(token);
	}
}
