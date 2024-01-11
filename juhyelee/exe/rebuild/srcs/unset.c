/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:38:46 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/11 18:28:53 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_unset(const char *arg, t_envp **list)
{
	char	**envs;
	size_t	index;
	t_envp	*p;

	arg += 6;
	if (arg[0] == '\0')
		return (EXIT_SUCCESS);
	envs = ft_split(arg, ' ');
	if (!envs)
		exit(EXIT_FAILURE);
	index = 0;
	while (envs[index])
	{
		p = *list;
		while (p)
		{
			if (ft_strncmp(p->variable, envs[index], \
							ft_strlen(p->variable)) == 0)
				remove_env(list, p);
			p = p->next;
		}
		index++;
	}
	return (EXIT_SUCCESS);
}

void	remove_env(t_envp **list, t_envp *to_del)
{
	t_envp	*to_del_prev;

	to_del_prev = *list;
	while (to_del_prev->next != to_del)
		to_del_prev = to_del_prev->next;
	to_del_prev->next = to_del->next;
	free(to_del->variable);
	free(to_del->value);
	free(to_del);
}
