#include "minishell.h"

t_simple	*make_simple_command(t_token *front, t_command *com)
{
	t_simple	*simple;

	simple = malloc(sizeof(t_simple));
	if (!simple)
		exit (-1);
	if (!front)
		return (simple);
	simple->command = NULL;
	simple->ward = NULL;
	if (front->type == COMMAND || front->type == WARD)
		simple->command = ft_strdup(front->str);
	else
		return (simple);
	if (front->next)
	{
		if (front->next->type == WARD)
			simple->ward = ft_strdup(front->next->str);
	}
	return (simple);
}

t_token	*add_back_rd(t_token *curr, t_redirection *rd)
{
	t_redirection	*new_rd;

	new_rd = init_redirection(new_rd);
	new_rd->symbol = ft_strdup(curr->str);
	if (!curr->next)
		new_rd->file = ft_strdup("");
	else if (curr->next->type == WARD)
		new_rd->file = ft_strdup(curr->next->str);
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
				break;
		}
		if (curr->type == PIPE)
			break;
		curr = curr->next;
	}
	rd = head->next;
	free (head);
	return (rd);
}

t_command	*make_command(t_token *front)
{
	t_command		*com;
	t_redirection	*last;

	com = init_com(com);
	com->simple_command = make_simple_command(front, com);
	com->redirection = make_redirection(front, com);
	return (com);
}

t_token	*find_next_front(t_token *front)
{
	while (front)
	{
		front = front->next;
		if (!front)
			break;
		if (front->type == PIPE)
		{
			front = front->next;
			break;
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
			break;
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

t_pipe	*make_pipe_tree(t_pipe *pipe, t_token *token)
{
	t_token	*front;
	t_token	*curr;
	t_pipe	*next_pipe;
	int		cnt;

	pipe = init_pipe(pipe);
	front = token;
	curr = token;
	next_pipe = pipe;
	cnt = 0;
	while (curr)
	{
		if (curr->type == PIPE)
		{
			curr = curr->next;
			next_pipe = new_pipe(pipe, front);
			front = find_next_front(front);
			cnt++;
			if (!curr)
				break;
		}
		curr = curr->next;
	}
	if (!cnt)
		pipe = new_pipe(pipe, front);
	else
		next_pipe = new_pipe(pipe, front);
	return (pipe);
}