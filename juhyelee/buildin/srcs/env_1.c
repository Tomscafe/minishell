/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:17:13 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/04 10:25:59 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buildin.h"

char	**add_envs(const char *envs[], const char *env)
{
	char	**new_envs;
	size_t	size;

	size = get_envs_size(envs);
	new_envs = create_new_envs(size + 2);
	if (!new_envs)
		return (NULL);
	if (!copy_envs(new_envs, envs))
		return (NULL);
	new_envs[size] = ft_strdup(env);
	if (!new_envs[size])
	{
		clear_envs(new_envs);
		return (NULL);
	}
	clear_envs((char **)envs);
	return (new_envs);
}

int	del_envs(char *envs[], const char *env)
{
	const size_t	env_idx = find_env((const char **)envs, env);
	size_t			index;

	if (env_idx == (size_t)-1)
		return (0);
	index = env_idx + 1;
	while (envs[index])
	{
		envs[index - 1] = envs[index];
		index++;
	}
	return (1);
}

char	**dup_envs(const char *envp[])
{
	char	**envs;

	envs = create_new_envs(get_envs_size(envp) + 1);
	if (!envs)
		return (NULL);
	if (!copy_envs(envs, envp))
		return (NULL);
	return (envs);
}
