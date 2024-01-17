/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:18:49 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/17 22:54:43 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_export(t_proc proc, t_envp **list)
{
	size_t	index;
	char	**envs;
	char	*var;
	char	*val;

	proc.arg += 7;
	if (proc.arg[0] == '\0')
		return (print_env_for_export(proc, (const t_envp *)(*list)));
	envs = ft_split(proc.arg, ' ');
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

int	print_env_for_export(const t_proc proc, const t_envp *list)
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
			ft_putstr_fd("declare -x ", proc.output);
			ft_putstr_fd(list->variable, proc.output);
			if (list->value)
			{
				ft_putchar_fd('=', proc.output);
				ft_putstr_fd(list->value, proc.output);
			}
			ft_putchar_fd('\n', proc.output);
			list = list->next;
		}
		exit(EXIT_SUCCESS);
	}
	waitpid(child, &exit_num, 0);
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

int	change_value(t_envp **list, const char *var, const char *val)
{
	t_envp	*p;

	p = *list;
	while (p)
	{
		if (ft_strncmp(p->variable, var, ft_strlen(p->variable) + 1) == 0)
		{
			free(p->value);
			p->value = (char *)val;
			return (1);
		}
		p = p->next;
	}
	return (0);
}
