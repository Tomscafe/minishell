/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:12:21 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/19 13:53:24 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(const char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

void	builtin(const t_proc proc, t_exe *exe)
{
	const char	**arg = (const char **)ft_split(proc.arg, -1);

	if (!arg)
		exit(EXIT_FAILURE);
	if (ft_strncmp(proc.cmd, "echo", 5) == 0)
		exe->st_exit = execute_echo(proc, &arg[1], exe->st_exit);
	else if (ft_strncmp(proc.cmd, "cd", 3) == 0)
		exe->st_exit = execute_cd(arg[1], exe);
	else if (ft_strncmp(proc.cmd, "pwd", 4) == 0)
		exe->st_exit = execute_pwd(proc, exe);
	else if (ft_strncmp(proc.cmd, "export", 7) == 0)
		exe->st_exit = execute_export(proc, &arg[1], exe->env);
	else if (ft_strncmp(proc.cmd, "unset", 6) == 0)
		exe->st_exit = execute_unset(&arg[1], exe->env);
	else if (ft_strncmp(proc.cmd, "env", 4) == 0)
		exe->st_exit = execute_env(proc, (const t_envp *)(*exe->env));
	else if (ft_strncmp(proc.cmd, "exit", 5) == 0)
		exe->st_exit = execute_exit(arg[1]);
	else
		exe->st_exit = EXIT_FAILURE;
	clear_strs((char **)arg);
}

int	execute_pwd(const t_proc proc, t_exe *exe)
{
	static char	buffer[PATH_MAX];
	pid_t		child;
	int			exit_num;

	child = fork();
	if (child < 0)
		exit(EXIT_FAILURE);
	else if (child == 0)
	{
		if (getcwd(buffer, PATH_MAX))
			ft_strlcpy(exe->pwd_pth, buffer, PATH_MAX);
		ft_putendl_fd(exe->pwd_pth, proc.output);
		exit(EXIT_SUCCESS);
	}
	waitpid(child, &exit_num, 0);
	return (WEXITSTATUS(exit_num));
}

int	execute_env(const t_proc proc, const t_envp *list)
{
	pid_t	child;
	int		exit_num;

	if (proc.arg[4] != '\0')
		return (printf("usage: env\n"), EXIT_FAILURE);
	child = fork();
	if (child < 0)
		exit(EXIT_FAILURE);
	else if (child == 0)
	{
		while (list)
		{
			if (list->value && list->value[0])
			{
				ft_putstr_fd(list->variable, proc.output);
				ft_putchar_fd('=', proc.output);
				ft_putendl_fd(list->value, proc.output);
			}
			list = list->next;
		}
		exit(EXIT_SUCCESS);
	}
	waitpid(child, &exit_num, 0);
	return (WEXITSTATUS(exit_num));
}

int	is_exist(const t_list *files, const char *file_name)
{
	t_file	*content;

	while (files)
	{
		content = files->content;
		if (ft_strncmp(content->name, file_name, \
					ft_strlen(content->name) + 1) == 0)
			return (1);
		files = files->next;
	}
	return (0);
}
