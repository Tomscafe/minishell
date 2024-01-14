/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_rd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hywoo <hywoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:46:08 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/14 14:46:44 by hywoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_heredoc(char *str)
{
	if (str[0] == '<')
	{
		if (str[1] == '<')
			return (1);
	}
	return (0);
}

t_token	*add_back_rd(t_token *curr, t_redirection *rd)
{
	t_redirection	*new_rd;

	new_rd = init_redirection(new_rd);
	new_rd->symbol = ft_strdup(curr->str);
	if (check_heredoc(new_rd->symbol))
		new_rd->file = ft_strdup(curr->next->str);
	else if (curr->next->type == WARD)
		new_rd->file = pipe_strdup(curr->env, curr->next->str);
	rd->next = new_rd;
	return (curr);
}

t_redirection	*last_redirection(t_redirection *rd)
{
	t_redirection	*last;

	last = rd;
	if (!rd)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

t_redirection	*make_redirection(t_token *front, t_command *com)
{
	t_redirection	*rd;
	t_redirection	*head;
	t_token			*curr;

	curr = front;
	rd = init_redirection(rd);
	head = rd;
	while (curr)
	{
		if (curr->type == REDIRECTION)
		{
			curr = add_back_rd(curr, rd);
			rd = rd->next;
			if (!curr)
				break ;
		}
		if (curr->type == PIPE)
			break ;
		curr = curr->next;
	}
	rd = head->next;
	free (head);
	return (rd);
}
