/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:33:57 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/09 19:45:18 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_cd(const t_table table, const int is_child)
{
	const char	**arg = (const char **)ft_split(table.argument, ' ');

	if (!arg)
	{
		fprintf(stderr, "cd: split error\n");
		exit(EXIT_FAILURE);
	}
	if (is_child)
	{
		close(table.inputfd);
		close(table.outputfd);
	}
	else
	{
		if (table.inputfd != STDIN_FILENO)
			close(table.inputfd);
		if (table.outputfd != STDOUT_FILENO)
			close(table.outputfd);
	}
	cd_core(arg);
}

void	cd_core(const char **arg)
{
	if (!arg[0])
		chdir("~");
	else if (chdir(arg[1]) == -1)
	{
		fprintf(stderr, "cd: %s: No such file or directory\n", arg[1]);
		return ;
	}
}

void	run_exit(const t_table table, const int is_child)
{
	const char	**arg = (const char **)ft_split(table.argument, ' ');
	int			exit_num;

	if (!arg)
	{
		fprintf(stderr, "exit: split error\n");
		exit(EXIT_FAILURE);
	}
	if (is_child)
	{
		close(table.inputfd);
		close(table.outputfd);
	}
	else
	{
		if (table.inputfd != STDIN_FILENO)
			close(table.inputfd);
		if (table.outputfd != STDOUT_FILENO)
			close(table.outputfd);
	}
	if (!arg[0])
		exit_num = 0;
	else
		exit_num = ft_atoi(arg[1]);
	exit(exit_num);
}

void	run_pwd(const t_table table, const int is_child)
{
	char	buffer[2024];

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
			dup2(table.outputfd, STDOUT_FILENO);
			close(table.outputfd);
		}
		if (table.inputfd != STDIN_FILENO)
			close(table.inputfd);
	}
	getcwd(buffer, 2024);
	printf("%s\n", buffer);
}

void	print_env(const t_envp *envp)
{
	while (envp)
	{
		if (envp->value)
			printf("%s=%s\n", envp->variable, envp->value);
		envp = envp->next;
	}
}
