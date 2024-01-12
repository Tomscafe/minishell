/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:51:20 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/12 14:04:24 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_table(t_table *table, const t_command cmd, \
				const int input, const int output)
{
	table->command = cmd.simple_command->command;
	table->argument = get_argument(*cmd.simple_command);
	if (!set_redirection(table, cmd.redirection, input, output))
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

int	set_redirection(t_table *table, const t_redirection *rd, \
					const int input, const int output)
{
	table->input = set_input(rd, input);
	table->output = set_output(rd, output);
	return (table->input >= 0);
}

int	set_input(const t_redirection *rd, const int indef)
{
	int	input;

	input = indef;
	while (rd)
	{
		if (ft_strncmp(rd->symbol, "<<", 2) == 0)
		{
			input = heredoc(rd->file);
			if (input < 0)
				return (-1);
		}
		else if (rd->symbol[0] == '<')
		{
			input = open(rd->file, O_RDONLY);
			if (input < 0)
			{
				printf("minishell: %s: No such file or directory\n", rd->file);
				return (-1);
			}
		}
		rd = rd->next;
	}
	return (input);
}

int	set_output(const t_redirection *rd, const int outdef)
{
	int	output;

	output = outdef;
	while (rd)
	{
		if (ft_strncmp(rd->symbol, ">>", 2) == 0)
		{
			if (output != STDOUT_FILENO)
				close(output);
			output = open(rd->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		}
		else if (rd->symbol[0] == '>')
		{
			if (output != STDOUT_FILENO)
				close(output);
			output = open(rd->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (output < 0)
			exit(EXIT_FAILURE);
		rd = rd->next;
	}
	return (output);
}
