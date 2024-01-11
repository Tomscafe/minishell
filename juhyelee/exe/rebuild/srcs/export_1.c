/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:18:49 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/11 18:22:53 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_export(const char *arg, t_envp **list)
{
	size_t	index;
	char	**envs;
	char	*var;
	char	*val;

	arg += 7;
	if (arg[0] == '\0')
		return (print_env_for_export((const t_envp *)(*list)), EXIT_SUCCESS);
	envs = ft_split(arg, ' ');
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
	return (EXIT_SUCCESS);
}

void	print_env_for_export(const t_envp *list)
{
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
	}
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
