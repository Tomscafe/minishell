/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:42:52 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/09 19:46:33 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin(t_table table, t_execution *exe, const int is_child)
{
	if (ft_strncmp(table.command, "echo", ft_strlen(table.command)) == 0)
		run_echo(table, is_child);
	if (ft_strncmp(table.command, "cd", ft_strlen(table.command)) == 0)
		run_cd(table, is_child);
	if (ft_strncmp(table.command, "exit", ft_strlen(table.command)) == 0)
		run_exit(table, is_child);
	if (ft_strncmp(table.command, "pwd", ft_strlen(table.command)) == 0)
		run_pwd(table, is_child);
	if (ft_strncmp(table.command, "export", ft_strlen(table.command)) == 0)
		run_export(table, exe, is_child);
	if (ft_strncmp(table.command, "unset", ft_strlen(table.command)) == 0)
		run_unset(table, exe, is_child);
	if (ft_strncmp(table.command, "env", ft_strlen(table.command)) == 0)
		run_env(table, *exe, is_child);
}

int	is_builtin(const char *command)
{
	if (ft_strncmp(command, "echo", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "exit", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "cd", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "export", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "unset", ft_strlen(command)) == 0)
		return (1);
	if (ft_strncmp(command, "env", ft_strlen(command)) == 0)
		return (1);
	return (0);
}

void	run_echo(const t_table table, const int is_child)
{
	const char	**arg = (const char **)ft_split(table.argument, ' ');

	if (!arg)
	{
		fprintf(stderr, "echo: split error\n");
		exit(EXIT_FAILURE);
	}
	if (is_child)
	{
		dup2(table.outputfd, STDOUT_FILENO);
		close(table.inputfd);
		close(table.outputfd);
	}
	else
	{
		if (table.outputfd != STDOUT_FILENO)
		{
			dup2(table.outputfd, STDERR_FILENO);
			close(table.outputfd);
		}
		if (table.inputfd != STDIN_FILENO)
			close(table.inputfd);
	}
	echo_core(arg);
}

// $? 처리
void	echo_core(const char **arg)
{
	int		is_newline;
	size_t	index;

	is_newline = 1;
	if (arg[1])
		is_newline = set_option(arg[1]);
	if (is_newline == -1)
		return ;
	index = 0;
	if (!is_newline)
		index++;
	while (arg[index + 1])
	{
		printf("%s ", arg[index]);
		index++;
	}
	if (arg[index])
		printf("%s", arg[index]);
	if (is_newline)
		printf("\n");
}

int	set_option(const char *arg)
{
	if (ft_strncmp(arg, "-n", ft_strlen(arg)) == 0)
		return (0);
	else if (arg[1] == '-')
	{
		fprintf(stderr, "echo: option error\n");
		return (-1);
	}
	return (1);
}
