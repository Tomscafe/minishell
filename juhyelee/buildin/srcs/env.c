/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:17:13 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/03 21:42:54 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buildin.h"

void	convert_env_list(t_list **list, const char *envp[])
{
	size_t	index;

	*list = NULL;
	index = 0;
	while (envp[index])
	{
		add_env(list, envp[index]);
		index++;
	}
}

void	print_error(const char *cmd, const char *message, const char *arg)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: %s: %s\n", cmd, arg, message);
}

void	add_env(t_list **env_list, const char *str)
{
	t_env	*env;
	t_list	*new_env;

	env = create_env(str);
	if (!env)
		exit(FAIL);
	new_env = ft_lstnew(env);
	if (!new_env)
		exit(FAIL);
	ft_lstadd_back(env_list, new_env);
}

t_env	*create_env(const char *str)
{
	char	**strs;
	t_env	*new_env;

	strs = ft_split(str, '=');
	if (!strs)
		return (NULL);
	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
	{
		clear_strs(strs);
		return (NULL);
	}
	new_env->env = ft_strdup(strs[0]);
	new_env->val = NULL;
	if (strs[1])
		new_env->val = ft_strdup(strs[1]);
	clear_strs(strs);
	return (new_env);
}
