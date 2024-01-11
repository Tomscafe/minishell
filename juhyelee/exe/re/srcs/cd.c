/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:53:01 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/11 16:16:26 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_cd(const char *arg, t_envp **list)
{
	char	*first_arg;

	arg += 3;
	change_oldpwd(list);
	if (arg[0] == '\0')
	{
		chdir("~");
		return (EXIT_SUCCESS);
	}
	first_arg = get_first_arg(arg);
	if (chdir(first_arg) < 0)
		return (free(first_arg), EXIT_FAILURE);
	free(first_arg);
	return (EXIT_SUCCESS);
}

void	change_oldpwd(t_envp **list)
{
	char	buffer[2024];
	char	*ret;
	t_envp	*oldpwd;

	ret = getcwd(buffer, 2024);
	if (!ret)
		return ;
	oldpwd = *list;
	while (oldpwd)
	{
		if (ft_strncmp(oldpwd->variable, "OLDPWD", \
						ft_strlen(oldpwd->variable)) == 0)
		{
			oldpwd->value = ret;
		}
		oldpwd = oldpwd->next;
	}
	free(ret);
}

char	*get_first_arg(const char *arg)
{
	size_t	size;
	char	*ret;

	size = 0;
	while (arg[size] && arg[size] != ' ')
		size++;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		exit(EXIT_FAILURE);
	ft_strlcpy(ret, arg, size + 1);
	return (ret);
}
