/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:19:09 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/04 11:45:43 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buildin.h"

int	contain_equ(const char *env)
{
	size_t	index;

	index = 0;
	while (env[index])
	{
		if (env[index] == '=')
			return (1);
		index++;
	}
	return (0);
}

void	unset_cmd(const size_t argc, const char *argv[], char *envs[])
{
	size_t	index;

	index = 1;
	while (index < argc)
	{
		del_envs(envs, argv[index]);
		index++;
	}
}

void	env_cmd(const char *envs[])
{
	size_t	index;

	close(STDIN_FILENO);
	index = 0;
	while (envs[index])
	{
		if (contain_equ(envs[index]))
			printf("%s\n", envs[index]);
		index++;
	}
}

char	**export_cmd(const size_t argc, const char *argv[], const char *envs[])
{
	size_t	index;
	char	**new_envs;

	close(STDIN_FILENO);
	if (argc == 1)
	{
		index = 0;
		while (envs[index])
		{
			printf("declare -x %s\n", envs[index]);
			index++;
		}
	}
	else
	{
		new_envs = add_envs(envs, argv[1]);
		index = 2;
		while (index < argc)
		{
			new_envs = add_envs((const char **)new_envs, argv[index]);
			index++;
		}
		return (new_envs);
	}
	return ((char **)envs);
}
