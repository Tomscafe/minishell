/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:40:41 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/19 15:57:22 by juhyelee         ###   ########.fr       */
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

int	execute_exit(const char *arg)
{
	int		exit_num;
	char	*to_comp;
	size_t	index;

	if (!arg)
		exit(0);
	exit_num = ft_atoi(arg);
	to_comp = ft_itoa(exit_num);
	if (arg[0] == '+')
		arg++;
	index = 0;
	if (ft_strncmp(arg, to_comp, ft_strlen(arg) + 1))
	{
		printf("exit\n");
		printf("minishell: exit: %s: numberic argument required\n", arg);
		exit(255);
	}
	free(to_comp);
	exit(exit_num % 255);
}
