/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:54:30 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/10 14:32:51 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_export(const t_table table, t_execution *exe, const int is_child)
{
	const char	**arg = (const char**)ft_split(table.argument, ' ');

	if (!arg)
	{
		fprintf(stderr, "export: split error\n");
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
		if (table.inputfd != STDIN_FILENO)
			close(table.inputfd);
		if (table.outputfd != STDOUT_FILENO)
		{
			dup2(table.outputfd, STDOUT_FILENO);
			close(table.outputfd);
		}
	}
	export_core(arg, exe);
}

void	export_core(const char **arg, t_execution *exe)
{
	t_envp	*p;
	size_t	index;

	p = exe->env;
	if (!arg[0])
	{
		while (p)
		{
			printf("declare -x %s=%s\n", p->variable, p->value);
			p = p->next;
		}
	}
	else
	{
		index = 1;
		while (arg[index])
		{
			if (!add_env(exe, arg[index]))
				return ;
			index++;
		}
	}
}

int	add_env(t_execution *exe, const char *str)
{
	const char	**value = (const char **)ft_split(str, '=');
	t_envp		*last;
	t_envp		*new_env;

	if (!value)
	{
		fprintf(stderr, "add env: split error\n");
		exit(EXIT_FAILURE);
	}
	last = exe->env;
	while (last->next)
		last = last->next;
	new_env = (t_envp *)malloc(sizeof(t_envp));
	if (!new_env)
	{
		clear_strs((char **)value);
		fprintf(stderr, "add env: malloc fail\n");
		return (0);
	}
	set_new_env(new_env, value);
	last->next = new_env;
	return (1);
}

void	set_new_env(t_envp *new_env, const char **value)
{
	new_env->variable = (char *)value[0];
	new_env->value = NULL;
	if (value[1])
		new_env->value = (char *)value[1];
	new_env->next = NULL;
}

void	run_env(const t_table table, const t_execution exe, const int is_child)
{
	if (is_child)
	{
		dup2(table.outputfd, STDOUT_FILENO);
		close(table.inputfd);
		close(table.outputfd);
	}
	else
	{
		if (table.inputfd != STDIN_FILENO)
			close(table.inputfd);
		if (table.outputfd != STDOUT_FILENO)
		{
			dup2(table.outputfd, STDOUT_FILENO);
			close(table.outputfd);
		}
	}
	print_env(exe.env);
}

