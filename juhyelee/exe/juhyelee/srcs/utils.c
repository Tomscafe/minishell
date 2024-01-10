/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:07:58 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/09 19:49:21 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_args(const t_table table)
{
	const char	**arg = (const char **)ft_split(table.argument, ' ');
	char		**args;
	size_t		size;

	if (!arg)
	{
		fprintf(stderr, "get args: split error\n");
		exit(EXIT_FAILURE);
	}
	size = get_strs_size(arg);
	args = init_args((const char **)arg);
	args[0] = ft_strdup(table.command);
	if (!args[0])
	{
		fprintf(stderr, "get args: strdup error\n");
		exit(EXIT_FAILURE);
	}
	copy_strs(&(args[1]), arg);
	return (args);
}

size_t	get_strs_size(const char **strs)
{
	size_t	size;

	size = 0;
	while (strs[size])
		size++;
	return (size);
}

char	**init_args(const char **arg)
{
	char	**ret;
	size_t	size;

	size = get_strs_size(arg);
	ret = (char **)malloc(sizeof(char *) * (size + 2));
	if (!ret)
	{
		fprintf(stderr, "init args: fail malloc\n");
		exit(EXIT_FAILURE);
	}
	ft_memset(ret, 0, sizeof(char *) * (size + 2));
	return (ret);
}

void	copy_strs(char **dest, const char **org)
{
	size_t	index;

	index = 0;
	while (org[index])
	{
		ft_strlcpy(dest[index], org[index], ft_strlen(org[index]));
		index++;
	}
	dest[index] = NULL;
}

void	close_pipe(int *pipe)
{
	close(pipe[WRITE]);
	close(pipe[READ]);
}
