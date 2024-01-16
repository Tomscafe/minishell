/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:12:21 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/16 19:54:01 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(const char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		return (1);
	return (0);
}

void	builtin(const t_table table, t_exe *exe)
{
	if (ft_strncmp(table.command, "echo", ft_strlen(table.command)) == 0)
		exe->st_exit = execute_echo(table, exe->st_exit);
	else if (ft_strncmp(table.command, "cd", ft_strlen(table.command)) == 0)
		exe->st_exit = execute_cd(table.argument, exe->env);
	else if (ft_strncmp(table.command, "pwd", ft_strlen(table.command)) == 0)
		exe->st_exit = execute_pwd(table);
	else if (ft_strncmp(table.command, "export", ft_strlen(table.command)) == 0)
		exe->st_exit = execute_export(table, exe->env);
	else if (ft_strncmp(table.command, "unset", ft_strlen(table.command)) == 0)
		exe->st_exit = execute_unset(table.argument, exe->env);
	else if (ft_strncmp(table.command, "env", ft_strlen(table.command)) == 0)
		exe->st_exit = execute_env(table, (const t_envp *)(*exe->env));
	else if (ft_strncmp(table.command, "exit", ft_strlen(table.command)) == 0)
		exe->st_exit = execute_exit(table.argument);
	else
		exe->st_exit = EXIT_FAILURE;
}

void	builtin_output(int input, int output)
{
	if (output != STDOUT_FILENO)
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}
	close(STDIN_FILENO);
	close(input);
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
		builtin_output(table.input, table.output);
		ret = getcwd(buffer, 2024);
		if (!ret)
			return (EXIT_FAILURE);
		ft_putendl_fd(buffer, STDIN_FILENO);
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
		builtin_output(table.input, table.output);
		while (list)
		{
			if (list->value && list->value[0])
			{
				ft_putstr_fd(list->variable, STDOUT_FILENO);
				ft_putchar_fd('=', STDOUT_FILENO);
				ft_putendl_fd(list->value, STDOUT_FILENO);
			}
			list = list->next;
		}
		exit(EXIT_SUCCESS);
	}
	waitpid(child, &exit_num, 0);
	return (WEXITSTATUS(exit_num));
}
