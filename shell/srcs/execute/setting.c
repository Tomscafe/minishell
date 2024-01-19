/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:51:20 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/19 15:51:49 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_proc(t_proc *proc, const t_setting setting)
{
	proc->input = setting.input;
	proc->output = setting.output;
	if (!set_redirection(proc, (const t_list *)setting.files, setting.cmd))
		return (0);
	if (!setting.cmd.simple_command->command)
		return (0);
	proc->cmd = setting.cmd.simple_command->command;
	proc->arg = get_argument(*setting.cmd.simple_command);
	return (1);
}

int	set_redirection(t_proc *proc, const t_list *files, t_command cmd)
{
	while (cmd.redirection)
	{
		if (!set_file(proc, files, *cmd.redirection))
			return (0);
		cmd.redirection = cmd.redirection->next;
	}
	return (1);
}

int	set_file(t_proc *proc, const t_list *files, const t_redirection rd)
{
	t_file	*content;
	t_redir	redir;

	while (files)
	{
		content = files->content;
		redir = where_is(content->name, rd);
		if (redir == e_heredoc || redir == e_input)
			proc->input = content->io[READ];
		else if (redir == e_output)
			proc->output = content->io[WRITE];
		if (proc->input < 0)
		{
			printf("minishell: %s: no such file or directory\n", content->name);
			return (0);
		}
		files = files->next;
	}
	return (1);
}

int	where_is(const char *file, const t_redirection rd)
{
	if (ft_strncmp(file, rd.file, ft_strlen(file) + 1) == 0)
	{
		if (ft_strncmp(rd.symbol, "<<", 2) == 0)
			return (e_heredoc);
		else if (rd.symbol[0] == '<')
			return (e_input);
		else
			return (e_output);
	}
	return (0);
}

char	*get_argument(const t_simple cmd)
{
	const size_t	cmd_len = ft_strlen(cmd.command);
	const size_t	arg_len = ft_strlen(cmd.ward);
	const size_t	size = cmd_len + arg_len + 2;
	const char		tmp[2] = {-1, 0};
	char			*ret;

	ret = (char *)malloc(sizeof(char) * size);
	if (!ret)
		exit(EXIT_FAILURE);
	ft_strlcpy(ret, cmd.command, size);
	ft_strlcat(ret, tmp, size);
	ft_strlcat(ret, cmd.ward, size);
	return (ret);
}
