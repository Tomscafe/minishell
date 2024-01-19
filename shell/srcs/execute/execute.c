/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 03:41:33 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/19 22:15:53 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute(t_pipe *cmds, t_envp **env)
{
	static t_exe	exe;

	if (cmds->first->simple_command->command && \
		cmds->first->simple_command->command[0] == '\0')
		return ;
	exe.cmds = cmds;
	exe.env = env;
	exe.n_cmd = get_num_cmd(cmds);
	exe.p_pipe = NO_FILE;
	getcwd(exe.pwd_pth, PATH_MAX);
	if (!open_all_files(&exe))
	{
		ft_lstclear(&(exe.files), clear_when_signal);
		unlink(HD);
		return ;
	}
	if (exe.n_cmd == 1)
		process_one_command(&exe);
	else
		process_commands(&exe);
	ft_signal();
	ft_lstclear(&(exe.files), clear_file);
	unlink(HD);
}

void	process_one_command(t_exe *exe)
{
	t_proc		proc;
	t_setting	setting;

	setting.files = exe->files;
	setting.cmd = *exe->cmds->first;
	setting.input = STDIN_FILENO;
	setting.output = STDOUT_FILENO;
	if (!set_proc(&proc, setting, exe->st_exit))
	{
		exe->st_exit = EXIT_FAILURE;
		return ;
	}
	if (is_builtin(proc.cmd))
		builtin(proc, exe);
	else
		exe->st_exit = execute_one_command(proc, exe);
	free(proc.arg);
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

void	close_file(int fd)
{
	if (fd == STDIN_FILENO || fd == STDOUT_FILENO)
		return ;
	close(fd);
}
