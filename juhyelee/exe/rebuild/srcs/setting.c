/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:51:20 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/16 22:09:46 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_table(t_table *table, const t_exe *exe, const int index)
{
	t_command	cmd;

	table->input = exe->p_pipe;
	if (index == 0 || index == ONE_CMD)
		table->input = STDIN_FILENO;
	table->output = table->pipefd[WRITE];
	if (index + 1 == (int)exe->n_cmd || index == ONE_CMD)
		table->output = STDOUT_FILENO;
	cmd = *exe->cmds->first;
	if (index + 1 == (int)exe->n_cmd)
		cmd = *exe->cmds->second;
	table->command = cmd.simple_command->command;
	table->argument = get_argument(*cmd.simple_command);
	if (!set_redirection(table, (const t_list *)exe->files, cmd))
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

int	set_redirection(t_table *table, const t_list *files, t_command cmd)
{
	while (cmd.redirection)
	{
		if (!set_file(table, files, *cmd.redirection))
			return (0);
		cmd.redirection = cmd.redirection->next;
	}
	return (1);
}

int	set_file(t_table *table, const t_list *files, const t_redirection rd)
{
	t_file	*content;

	while (files)
	{
		content = files->content;
		if (content->is_heredoc)
		{
			table->is_heredoc = 1;
			table->input = content->io[READ];
			if (table->input <= 1)
				return (0);
		}
		else if (ft_strncmp(rd.file, content->name, \
							ft_strlen(content->name)) == 0 && \
				rd.symbol[0] == '>')
			table->output = content->io[WRITE];
		else if (rd.symbol[0] == '<' && rd.symbol[1] == '\0')
			table->input = content->io[READ];
		files = files->next;
	}
	return (1);
}

void	clear_file(void *to_del)
{
	t_file	*file;

	file = to_del;
	if (file->io[READ] <= 1)
		close(file->io[READ]);
	if (file->io[WRITE] <= 1)
		close(file->io[READ]);
	free(file);
}

char	*get_infile(const t_redirection *rd, int *is_heredoc)
{
	char	*infile;

	infile = NULL;
	*is_heredoc = 0;
	while (rd)
	{
		if (ft_strncmp(rd->symbol, "<<", 2) == 0)
		{
			infile = rd->file;
			*is_heredoc = 1;
		}
		else if (rd->symbol[0] == '<')
		{
			infile = rd->file;
			*is_heredoc = 0;
		}
		rd = rd->next;
	}
	return (infile);
}

char	*get_outfile(const t_redirection *rd, int *is_append)
{
	char	*outfile;

	outfile = NULL;
	*is_append = 0;
	while (rd)
	{
		if (ft_strncmp(rd->symbol, ">>", 2) == 0)
		{
			outfile = rd->file;
			*is_append = 1;
		}
		else if (rd->symbol[0] == '>')
		{
			outfile = rd->file;
			*is_append = 0;
		}
		rd = rd->next;
	}
	return (outfile);
}
