/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:17:48 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/13 12:55:01 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_pipe_table(t_table *table, const t_command cmd, \
					const int input, const int *pipefd)
{
	char	*infile;

	infile = NULL;
	table->command = cmd.simple_command->command;
	table->argument = get_argument(*cmd.simple_command);
	table->indef = input;
	table->outdef = pipefd[WRITE];
	table->is_heredoc = 0;
	table->input = set_inputdir(table, cmd.redirection, infile);
	table->output = set_output(table, cmd.redirection);
	if (table->input < 0)
		table->input = input;
}

int	set_inputdir(t_table *table, const t_redirection *rd, char *file)
{
	table->input = -1;
	while (rd)
	{
		file = rd->symbol;
		if (ft_strncmp(rd->symbol, "<<", 2) == 0)
		{
			close_input(table->input, -1);
			table->input = heredoc(rd->file);
			if (table->input >= 0)
				table->is_heredoc = 1;
		}
		else if (rd->symbol[0] == '<')
		{
			close_input(table->input, -1);
			table->input = open(rd->file, O_RDONLY);
		}
		rd = rd->next;
	}
	return (table->input);
}

void	close_input(int input, int indef)
{
	if (input != indef)
		close(input);
}

void	close_output(int output, int outdef)
{
	if (output != outdef)
		close(output);
}
