/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:17:48 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/16 00:46:35 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_pipe_table(t_table *table, const t_command cmd, \
					const int input, const int *pipefd)
{
	table->command = cmd.simple_command->command;
	table->argument = get_argument(*cmd.simple_command);
	table->indef = input;
	table->outdef = pipefd[WRITE];
	table->is_heredoc = 0;
	table->input = set_inputdir(table, cmd.redirection);
	table->output = set_output(table, cmd.redirection);
	if (table->input < 0)
		table->input = input;
}

int	set_inputdir(t_table *table, const t_redirection *rd)
{
	table->input = -1;
	while (rd)
	{
		if (ft_strncmp(rd->symbol, "<<", 2) == 0)
		{
			close_input(table->input);
			table->input = heredoc(rd->file);
			if (table->input >= 0)
				table->is_heredoc = 1;
		}
		else if (rd->symbol[0] == '<')
		{
			close_input(table->input);
			table->input = open(rd->file, O_RDONLY);
			if (table->input < 0)
				return (printf("minishell: %s: No such file or directory\n", \
							rd->file), -1);
		}
		rd = rd->next;
	}
	return (table->input);
}

void	close_input(int input)
{
	if (input != STDIN_FILENO)
		close(input);
}

void	close_output(int output)
{
	if (output != STDOUT_FILENO)
		close(output);
}
