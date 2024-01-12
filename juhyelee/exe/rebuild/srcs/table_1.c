/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:51:20 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/12 19:47:35 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_table(t_table *table, const t_command cmd, \
				const int input, const int output)
{
	table->indef = input;
	table->outdef = output;
	table->command = cmd.simple_command->command;
	table->argument = get_argument(*cmd.simple_command);
	if (!set_redirection(table, cmd.redirection))
		return (0);
	return (1);
}

char	*get_argument(const t_simple cmd)
{
	const size_t	cmd_len = ft_strlen(cmd.command);
	const size_t	arg_len = ft_strlen(cmd.ward);
	const size_t	size = cmd_len + arg_len + 2;
	char			*ret;

	ret = (char *)malloc(sizeof(char) * size);
	if (!ret)
		exit(EXIT_FAILURE);
	ft_strlcpy(ret, cmd.command, size);
	ft_strlcat(ret, " ", size);
	ft_strlcat(ret, cmd.ward, size);
	return (ret);
}

int	set_redirection(t_table *table, const t_redirection *rd)
{
	table->input = set_input(table, rd);
	table->output = set_output(table, rd);
	return (table->input >= 0);
}

int	set_input(t_table *table, const t_redirection *rd)
{
	table->input = table->indef;
	while (rd)
	{
		if (ft_strncmp(rd->symbol, "<<", 2) == 0)
		{
			close_input(table->input, table->indef);
			table->input = heredoc(rd->file);
			if (table->input < 0)
				return (-1);
			table->is_heredoc = 1;
		}
		else if (rd->symbol[0] == '<')
		{
			close_input(table->input, table->outdef);
			table->input = open(rd->file, O_RDONLY);
			if (table->input < 0)
			{
				printf("minishell: %s: No such file or directory\n", rd->file);
				return (-1);
			}
		}
		rd = rd->next;
	}
	return (table->input);
}

int	set_output(t_table *table, const t_redirection *rd)
{
	table->output = table->outdef;
	while (rd)
	{
		if (ft_strncmp(rd->symbol, ">>", 2) == 0)
		{
			close_output(table->output, table->outdef);
			table->output = open(rd->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		}
		else if (rd->symbol[0] == '>')
		{
			close_output(table->output, table->outdef);
			table->output = open(rd->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (table->output < 0)
			exit(EXIT_FAILURE);
		rd = rd->next;
	}
	return (table->output);
}
