/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:17:34 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/09 19:43:31 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**set_env(const t_envp *envp_list)
{
	char	**env;
	size_t	index;
	size_t	env_size;

	env_size = get_env_list_size(envp_list);
	env = (char **)malloc(sizeof(char *) * (env_size + 1));
	if (!env)
	{
		fprintf(stderr, "set env: fail malloc\n");
		exit(EXIT_FAILURE);
	}
	ft_memset(env, 0, (env_size + 1) * sizeof(char *));
	index = 0;
	while (index < env_size)
	{
		env[index] = set_value(envp_list);
		if (!env[index])
		{
			clear_strs(env);
			return (NULL);
		}
		envp_list = envp_list->next;
		index++;
	}
	return (env);
}

size_t	get_env_list_size(const t_envp *envp_list)
{
	size_t	size;

	size = 0;
	while (envp_list)
	{
		size++;
		envp_list = envp_list->next;
	}
	return (size);
}

char	*set_value(const t_envp *const envp_list)
{
	const size_t	val_len = ft_strlen(envp_list->value);
	const size_t	var_len = ft_strlen(envp_list->variable);
	const size_t	value_len = val_len + var_len + 2;
	char			*value;

	value = (char *)malloc(sizeof(char) * value_len);
	if (!value)
	{
		fprintf(stderr, "set value: fail malloc\n");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(value, envp_list->variable, value_len);
	ft_strlcat(value, "=", value_len);
	if (envp_list->value)
		ft_strlcat(value, envp_list->variable, value_len);
	return (value);
}

void	clear_str(char **env)
{
	size_t	index;

	index = 0;
	while (env[index])
	{
		free(env[index]);
		index++;
	}
	free(env[index]);
}

int	set_redirection(t_table *table, const t_redirection *rd)
{
	while (rd)
	{
		if (ft_strncmp(rd->symbol, ">", 3) == 0)
			table->outputfd = \
				open(rd->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (ft_strncmp(rd->symbol, ">>", 3) == 0)
			table->outputfd = \
				open(rd->file, O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0644);
		else if (ft_strncmp(rd->symbol, "<", 3))
			table->inputfd = open(rd->file, O_RDONLY);
		else if (ft_strncmp(rd->symbol, "<<", 3) == 0)
			table->inputfd = heredoc(rd->file);
		if (table->inputfd == -1)
		{
			fprintf(stderr, "minishell: %s: No such file or directory\n", \
				rd->file);
			return (0);
		}
		rd = rd->next;
	}
	return (1);
}
