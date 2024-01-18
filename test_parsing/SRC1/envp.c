/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hywoo <hywoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:45:53 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/14 14:46:25 by hywoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_value(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str || !*str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	i++;
	result = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	while (str[i + j])
	{
		result[j] = str[i + j];
		j++;
	}
	result[j] = '\0';
	return (result);
}

char	*env_variable(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str || !*str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	result = malloc(sizeof(char) * i);
	while (j < i)
	{
		result[j] = str[j];
		j++;
	}
	result[j] = '\0';
	return (result);
}

t_envp	*new_env(char *str)
{
	t_envp	*new_envp;

	new_envp = malloc(sizeof(t_envp));
	if (!new_envp)
		exit (-1);
	new_envp->variable = env_variable(str);
	new_envp->value = env_value(str);
	new_envp->next = NULL;
	return (new_envp);
}

t_envp	*make_env(char **envp)
{
	t_envp	*env;
	t_envp	*curr;
	t_envp	*prev;
	int		i;

	i = 1;
	env = new_env(envp[0]);
	curr = env;
	while (envp[i])
	{
		prev = curr;
		curr = new_env(envp[i]);
		prev->next = curr;
		i++;
	}
	return (env);
}
