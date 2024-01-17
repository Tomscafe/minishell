/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:51:20 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/17 20:19:22 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_proc(t_proc *proc, const t_exe *exe, const int index)
{
	t_command	cmd;

	if (index == 0 || index == ONE_CMD)
		proc->input = STDIN_FILENO;
	else
		proc->input = exe->p_pipe;
	if (index + 1 == (int)exe->n_cmd || index == ONE_CMD)
		proc->output = STDOUT_FILENO;
	else
		proc->output = proc->pipefd[WRITE];
	if (index + 1 == (int)exe->n_cmd)
		cmd = *exe->cmds->second;
	else
		cmd = *exe->cmds->first;
	if (!set_redirection(proc, (const t_list *)exe->files, cmd))
		return (0);
	if (!cmd.simple_command->command)
		return (0);
	proc->cmd = cmd.simple_command->command;
	proc->arg = get_argument(*cmd.simple_command);
	printf("command : %s | input : %d | outpue : %d\n", proc->cmd, proc->input, proc->output);
	printf("pipe 0 : %d | pipe 1 : %d | prev : %d\n\n", proc->pipefd[0], proc->pipefd[1], exe->p_pipe);
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

int	set_file(t_proc *table, const t_list *files, const t_redirection rd)
{
	t_file	*content;

	while (files)
	{
		content = files->content;
		if (rd.symbol[0] == '<')
			table->input = content->io[READ];
		else
		{
			table->output = content->io[WRITE];
			if (table->output < 0)
			{
				printf("minishell: %s: no such file or directory\n", \
						content->name);
				return (0);
			}
		}
		files = files->next;
	}
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

int	execute_exit(const char *arg)
{
	int	exit_num;

	arg += 5;
	if (arg[0] == '\0')
		exit(0);
	exit_num = ft_atoi(arg) % 256;
	exit(exit_num);
}

