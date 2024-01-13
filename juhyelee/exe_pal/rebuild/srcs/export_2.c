/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:35:45 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/11 18:23:24 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	change_value(t_envp **list, const char *var, const char *val)
{
	t_envp	*p;

	p = *list;
	while (p)
	{
		if (ft_strncmp(p->variable, var, ft_strlen(p->variable)) == 0)
		{
			free(p->value);
			p->value = (char *)val;
			return (1);
		}
		p = p->next;
	}
	return (0);
}

void	add_variable(t_envp **list, const char *var, const char *val)
{
	t_envp	*last;
	t_envp	*new_env;

	last = *list;
	while (last->next)
		last = last->next;
	new_env = (t_envp *)malloc(sizeof(t_envp));
	if (!new_env)
		exit(EXIT_FAILURE);
	new_env->variable = (char *)var;
	new_env->value = (char *)val;
	new_env->next = NULL;
	if (!*list)
		*list = new_env;
	else
		last->next = new_env;
}
