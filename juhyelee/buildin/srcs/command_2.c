/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 21:19:09 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/03 21:50:01 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buildin.h"

void	export_cmd(t_list **env_list, const size_t argc, const char *argv[])
{
	close(STDIN_FILENO);
	if (argc == 1)
		print_envs(*env_list);
	else
		reg_envs(env_list, argc, argv);
}

void	print_envs(t_list *env_list)
{
	t_list	*p;
	t_env	*env;

	p = env_list;
	while (p)
	{
		env = p->content;
		printf("declare -x %s", env->env);
		if (env->val)
			printf("=\"%s\"", env->val);
		printf("\n");
		p = p->next;
	}
}

void	reg_envs(t_list **env_list, const size_t argc, const char *argv[])
{
	size_t	index;

	index = 1;
	while (index < argc)
	{
		add_env(env_list, argv[index]);
		index++;
	}
}

void	unset_cmd(t_list **env_list, const size_t argc, const char *argv[])
{
	size_t	index;
	t_list	*p;
	t_env	*env;

	if (argc > 1)
	{
		index = 0;
		while (index < argc)
		{
			p = *env_list;
			while (p)
			{
				env = p->content;
				if (ft_strncmp(argv, env->env, ft_strlen(argv)) == 0)
				p = p->next;
			}
			index++;
		}
	}
}

void	env_cmd(t_list *env_list)
{
	t_list	*p;
	t_env	*env;

	close(STDIN_FILENO);
	p = env_list;
	while (p)
	{
		env = p->content;
		if (env->val)
			printf("%s=%s\n", env->env, env->val);
		p = p->next;
	}
}
