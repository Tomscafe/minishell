/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:46:13 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/20 00:35:17 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*make_command(t_token *front)
{
	t_command		*com;

	com = init_com(NULL);
	com->simple_command = make_simple_command(front);
	com->redirection = make_redirection(front);
	if (front)
		get_simple(front->env, com->simple_command, com->redirection);
	return (com);
}

t_token	*find_next_front(t_token *front)
{
	while (front)
	{
		front = front->next;
		if (!front)
			break ;
		if (front->type == PIPE)
		{
			front = front->next;
			break ;
		}
	}
	return (front);
}

t_pipe	*last_pipe(t_pipe *pipe)
{
	t_pipe	*last;

	last = pipe;
	while (last)
	{
		if (!last->next)
			break ;
		last = last->next;
	}
	return (last);
}

t_pipe	*new_pipe(t_pipe *pipe, t_token *front)
{
	t_pipe	*new_pipe;

	if (!pipe->first)
	{
		pipe->first = make_command(front);
		return (pipe);
	}
	if (!pipe->second)
	{
		pipe->second = make_command(front);
		return (pipe);
	}
	new_pipe = init_pipe(pipe);
	new_pipe->first = last_pipe(pipe)->second;
	new_pipe->second = make_command(front);
	last_pipe(pipe)->next = new_pipe;
	return (new_pipe);
}

t_pipe	*make_pipe_tree(t_pipe *pipe, t_pipe *next_pipe,
							t_token *token, int cnt)
{
	t_token	*front;
	t_token	*curr;

	pipe = init_pipe(pipe);
	front = token;
	curr = token;
	next_pipe = pipe;
	while (curr)
	{
		if (curr->type == PIPE)
		{
			curr = curr->next;
			next_pipe = new_pipe(pipe, front);
			front = find_next_front(front);
			cnt++;
			if (!curr)
				break ;
		}
		curr = curr->next;
	}
	if (!cnt)
		pipe = new_pipe(pipe, front);
	else
		next_pipe = new_pipe(pipe, front);
	return (pipe);
}
