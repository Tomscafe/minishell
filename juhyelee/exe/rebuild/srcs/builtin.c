/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:12:21 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/12 13:06:36 by juhyelee         ###   ########.fr       */
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

int	builtin(const t_table table, t_envp **list, const int n_exit)
{
	if (ft_strncmp(table.command, "echo", ft_strlen(table.command)) == 0)
		return (execute_echo(table, n_exit));
	if (ft_strncmp(table.command, "cd", ft_strlen(table.command)) == 0)
		return (execute_cd(table.argument, list));
	if (ft_strncmp(table.command, "pwd", ft_strlen(table.command)) == 0)
		return (execute_pwd(table));
	if (ft_strncmp(table.command, "export", ft_strlen(table.command)) == 0)
		return (execute_export(table, list));
	if (ft_strncmp(table.command, "unset", ft_strlen(table.command)) == 0)
		return (execute_unset(table.argument, list));
	if (ft_strncmp(table.command, "env", ft_strlen(table.command)) == 0)
		return (execute_env(table, (const t_envp *)(*list)));
	if (ft_strncmp(table.command, "exit", ft_strlen(table.command)) == 0)
		return (execute_exit(table.argument));
	return (EXIT_FAILURE);
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
