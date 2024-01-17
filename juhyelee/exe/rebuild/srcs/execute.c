/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 03:41:33 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/17 17:59:15 by juhyelee         ###   ########.fr       */
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
		ft_lstclear(&(exe.files), clear_file);
		unlink("heredoc");
	}
	t_list *f = exe.files;
	while (f)
	{
		t_file *c = f->content;
		printf("%s : %d %d\n", c->name, c->io[0], c->io[1]);
		f= f->next;
	}
	//if (exe.n_cmd == 1)
	//	process_one_command(&exe);
	//else
	//	process_commands(&exe);
	//signal(SIGINT, handler);
	ft_lstclear(&(exe.files), clear_file);
	unlink("heredoc");
}

//void	process_one_command(t_exe *exe)
//{
//	t_table	table;

//	if (!set_table(&table, exe, ONE_CMD))
//	{
//		exe->st_exit = EXIT_FAILURE;
//		return ;
//	}
//	if (is_builtin(table.command) && !(table.flag & e_sig))
//		builtin(table, exe);
//	else if (!(table.flag & e_sig))
//		exe->st_exit = execute_one_command(table, *exe->env);
//}

//void	process_commands(t_exe *exe)
//{
//	t_table	*tables;
//	size_t	index;
//	int		st_ret;

//	tables = (t_table *)malloc(sizeof(t_table) * exe->n_cmd);
//	if (!tables)
//		exit(EXIT_FAILURE);
//	pipe_command(&tables[0], exe, 0);
//	index = 1;
//	while (exe->cmds->next)
//	{
//		exe->cmds = exe->cmds->next;
//		pipe_command(&tables[index], exe, index);
//		index++;
//	}
//	if (exe->cmds->second)
//		last_command(&tables[index], exe);
//	index = 0;
//	while (index < exe->n_cmd)
//	{
//		waitpid(tables[index].pid, &st_ret, WUNTRACED);
//		index++;
//	}
//	exe->st_exit = WEXITSTATUS(st_ret);
//	free(tables);
//}

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
