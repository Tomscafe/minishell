/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:12:21 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/17 15:05:51 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	builtin(const t_table table, t_exe *exe)
{
	if (ft_strncmp(table.command, "echo", 5) == 0)
		exe->st_exit = execute_echo(table, exe->st_exit);
	else if (ft_strncmp(table.command, "cd", 3) == 0)
		exe->st_exit = execute_cd(table.argument, exe->env);
	else if (ft_strncmp(table.command, "pwd", 4) == 0)
		exe->st_exit = execute_pwd(table);
	else if (ft_strncmp(table.command, "export", 7) == 0)
		exe->st_exit = execute_export(table, exe->env);
	else if (ft_strncmp(table.command, "unset", 6) == 0)
		exe->st_exit = execute_unset(table.argument, exe->env);
	else if (ft_strncmp(table.command, "env", 4) == 0)
		exe->st_exit = execute_env(table, (const t_envp *)(*exe->env));
	else if (ft_strncmp(table.command, "exit", 5) == 0)
		exe->st_exit = execute_exit(table.argument);
	else
		exe->st_exit = EXIT_FAILURE;
}

int	execute_pwd(const t_table table)
{
	pid_t	child;
	int		exit_num;
	char	buffer[2024];
	char	*ret;

	child = fork();
	if (child < 0)
		exit(EXIT_FAILURE);
	else if (child == 0)
	{
		ret = getcwd(buffer, 2024);
		if (!ret)
			return (EXIT_FAILURE);
		ft_putendl_fd(buffer, table.output);
		exit(EXIT_SUCCESS);
	}
	waitpid(child, &exit_num, 0);
	return (WEXITSTATUS(exit_num));
}

int	execute_env(const t_table table, const t_envp *list)
{
	pid_t	child;
	int		exit_num;

	child = fork();
	if (child < 0)
		exit(EXIT_FAILURE);
	else if (child == 0)
	{
		while (list)
		{
			if (list->value && list->value[0])
			{
				ft_putstr_fd(list->variable, table.output);
				ft_putchar_fd('=', table.output);
				ft_putendl_fd(list->value, table.output);
			}
			list = list->next;
		}
		exit(EXIT_SUCCESS);
	}
	waitpid(child, &exit_num, 0);
	return (WEXITSTATUS(exit_num));
}
