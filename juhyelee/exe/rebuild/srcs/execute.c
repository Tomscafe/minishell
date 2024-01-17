/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 03:41:33 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/17 19:44:31 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_pipe *cmds, t_envp **env)
{
	static t_exe	exe;

	exe.cmds = cmds;
	exe.env = env;
	exe.n_cmd = get_num_cmd(cmds);
	if (!open_all_files(&exe))
	{
		ft_lstclear(&(exe.files), clear_when_signal);
		unlink("heredoc");
		return ;
	}
	if (exe.n_cmd == 1)
		process_one_command(&exe);
	else
		process_commands(&exe);
	signal(SIGINT, handler);
	ft_lstclear(&(exe.files), clear_file);
	unlink("heredoc");
}

void	process_one_command(t_exe *exe)
{
	t_proc	proc;

	if (!set_proc(&proc, exe, ONE_CMD))
	{
		exe->st_exit = EXIT_FAILURE;
		return ;
	}
	if (is_builtin(proc.cmd))
		builtin(proc, exe);
	else
		exe->st_exit = execute_one_command(proc, *exe->env);
}

void	process_commands(t_exe *exe)
{
	t_proc	*procs;
	size_t	index;
	int		st_ret;

	procs = (t_proc *)malloc(sizeof(t_proc) * exe->n_cmd);
	if (!procs)
		exit(EXIT_FAILURE);
	pipe_command(&procs[0], exe, 0);
	index = 1;
	while (exe->cmds->next)
	{
		exe->cmds = exe->cmds->next;
		pipe_command(&procs[index], exe, index);
		index++;
	}
	if (exe->cmds->second)
		last_command(&procs[index], exe);
	index = 0;
	while (index < exe->n_cmd)
	{
		waitpid(procs[index].pid, &st_ret, WUNTRACED);
		index++;
	}
	exe->st_exit = WEXITSTATUS(st_ret);
	free(procs);
}

size_t	get_num_cmd(const t_pipe *cmds)
{
	size_t	n_cmd;

	n_cmd = 1;
	while (cmds->next)
	{
		cmds = cmds->next;
		n_cmd++;
	}
	if (cmds->second)
		n_cmd++;
	return (n_cmd);
}
