/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 09:55:30 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/04 10:13:02 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buildin.h"

int	copy_envs(char *new_envs[], const char *org_envs[])
{
	size_t	index;

	index = 0;
	while (org_envs[index])
	{
		new_envs[index] = ft_strdup(org_envs[index]);
		if (!new_envs[index])
		{
			clear_envs(new_envs);
			return (0);
		}
		index++;
	}
	return (1);
}

void	clear_envs(char *envs[])
{
	size_t	index;

	index = 0;
	while (envs[index])
	{
		free(envs[index]);
		index++;
	}
	free(envs);
}

char	**create_new_envs(const size_t size)
{
	char	**new_envs;

	new_envs = (char **)malloc(sizeof(char *) * size);
	if (!new_envs)
		return (NULL);
	ft_memset(new_envs, 0, size);
	return (new_envs);
}

size_t	get_envs_size(const char *envs[])
{
	size_t	size;

	size = 0;
	while (envs[size])
		size++;
	return (size);
}

size_t	find_env(const char *envs[], const char *env)
{
	size_t	index;

	index = 0;
	while (envs[index])
	{
		if (ft_strncmp(envs[index], env, ft_strlen(env)) == 0)
			return (index);
		index++;
	}
	return (-1);
}