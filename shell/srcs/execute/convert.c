/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:40:41 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/18 19:40:00 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**convert_to_array(const t_envp *list)
{
	char			**ret;
	size_t			size;
	size_t			index;
	const t_envp	*p = list;

	size = 0;
	while (p)
	{
		size++;
		p = p->next;
	}
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ret)
		exit(EXIT_FAILURE);
	index = 0;
	while (list)
	{
		ret[index] = get_env_string(list);
		index++;
		list = list->next;
	}
	ret[index] = NULL;
	return (ret);
}

void	remove_env(t_envp **list, t_envp *to_del)
{
	t_envp	*to_del_prev;

	to_del_prev = *list;
	while (to_del_prev->next != to_del)
		to_del_prev = to_del_prev->next;
	to_del_prev->next = to_del->next;
	free(to_del->variable);
	if (to_del->value)
		free(to_del->value);
	free(to_del);
}

char	*get_home(const t_envp *list)
{
	while (list)
	{
		if (ft_strncmp(list->variable, "HOME", ft_strlen(list->variable)) == 0)
			break ;
		list = list->next;
	}
	if (!list)
		return (NULL);
	return (ft_strdup(list->value));
}
