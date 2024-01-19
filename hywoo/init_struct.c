/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hywoo <hywoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:46:04 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/14 14:46:39 by hywoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*init_pipe(t_pipe *pipe)
{
	pipe = malloc(sizeof(t_pipe));
	if (!pipe)
		exit (-1);
	pipe->first = NULL;
	pipe->second = NULL;
	pipe->next = NULL;
	return (pipe);
}

t_command	*init_com(t_command *com)
{
	com = malloc(sizeof(t_command));
	if (!com)
		exit (-1);
	com->redirection = NULL;
	com->simple_command = NULL;
	return (com);
}

t_redirection	*init_redirection(t_redirection *rd)
{
	rd = malloc(sizeof(t_redirection));
	if (!rd)
		exit (-1);
	rd->symbol = NULL;
	rd->file = NULL;
	rd->next = NULL;
	rd->non = NULL;
	return (rd);
}
