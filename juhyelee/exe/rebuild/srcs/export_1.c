/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:18:49 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/12 13:05:06 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_export(t_table table, t_envp **list)
{
	size_t	index;
	char	**envs;
	char	*var;
	char	*val;

	table.argument += 7;
	if (table.argument[0] == '\0')
		return (print_env_for_export(table, (const t_envp *)(*list)));
	envs = ft_split(table.argument, ' ');
	if (!envs)
		exit(EXIT_FAILURE);
	index = 0;
	while (envs[index])
	{
		var = get_variable(envs[index]);
		val = get_value(envs[index]);
		if (!change_value(list, var, val))
			add_variable(list, var, val);
		index++;
	}
	clear_strs(envs);
	return (EXIT_SUCCESS);
}

int	print_env_for_export(const t_table table, const t_envp *list)
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
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(list->variable, STDOUT_FILENO);
			if (list->value)
			{
				ft_putchar_fd('=', STDOUT_FILENO);
				ft_putstr_fd(list->value, STDOUT_FILENO);
			}
			ft_putchar_fd('\n', STDOUT_FILENO);
			list = list->next;
		}
		exit(EXIT_SUCCESS);
	}
	waitpid(child, &exit_num, WUNTRACED);
	return (WEXITSTATUS(exit_num));
}

char	*get_variable(const char *env)
{
	char	*var;
	size_t	size;

	size = 0;
	while (env[size] && env[size] != '=')
		size++;
	var = (char *)malloc(sizeof(char) * (size + 1));
	if (!var)
		exit(EXIT_FAILURE);
	ft_strlcpy(var, env, size + 1);
	return (var);
}

char	*get_value(const char *env)
{
	char	*val;
	size_t	size;

	size = 0;
	while (env[size] && env[size] != '=')
		size++;
	size = ft_strlen(env + size);
	val = (char *)malloc(sizeof(char) * (size + 1));
	if (!val)
		exit(EXIT_FAILURE);
	ft_strlcpy(val, env, size + 1);
	return (val);
}
