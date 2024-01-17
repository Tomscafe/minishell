/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:45:58 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/17 22:55:26 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_simple(t_command *com)
{
	if (com->simple_command)
	{
		if (com->simple_command->command)
			free (com->simple_command->command);
		if (com->simple_command->ward)
			free (com->simple_command->ward);
		free (com->simple_command);
	}
}

void	free_command(t_command *com)
{
	t_redirection	*curr_rd;
	t_redirection	*next_rd;

	free_simple(com);
	if (com->redirection)
	{
		curr_rd = com->redirection;
		while (curr_rd)
		{
			next_rd = curr_rd->next;
			if (curr_rd->symbol)
				free(curr_rd->symbol);
			if (curr_rd->file)
				free(curr_rd->file);
			free (curr_rd);
			curr_rd = next_rd;
		}
	}
	free(com);
}

void	free_pipe(t_pipe *pipe, t_pipe *pipe_next)
{
	if (pipe)
	{
		while (pipe)
		{
			pipe_next = pipe->next;
			if (pipe->first)
				free_command(pipe->first);
			if (pipe->second)
			{
				free_command(pipe->second);
				if (pipe_next)
					pipe_next->first = NULL;
			}
			free (pipe);
			pipe = pipe_next;
		}
	}
}

void	all_free(t_token *token, t_pipe *pipe)
{
	t_token	*token_next;

	token_next = token;
	if (token)
	{
		while (token)
		{
			token_next = token->next;
			if (token->str)
				free(token->str);
			free(token);
			token = token_next;
		}
	}
	free_pipe (pipe, pipe);
}
