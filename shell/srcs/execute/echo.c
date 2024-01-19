/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:21:41 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/19 20:20:12 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_echo(t_proc proc, const char **arg)
{
	pid_t	child;
	int		exit_num;

	child = fork();
	if (child < 0)
		exit(EXIT_FAILURE);
	else if (child == 0)
	{
		if (!arg[0])
		{
			write(proc.output, "\n", 1);
			exit(EXIT_SUCCESS);
		}
		if (print_arg(proc.output, arg))
			write(proc.output, "\n", 1);
		exit(EXIT_SUCCESS);
	}
	waitpid(child, &exit_num, WUNTRACED);
	return (WEXITSTATUS(exit_num));
}

int	is_option(const char *arg)
{
	size_t	index;

	if (arg[0] != '-')
		return (0);
	index = 1;
	while (arg[index])
	{
		if (arg[index] != 'n')
			return (0);
		index++;
	}
	return (1);
}

int	print_arg(const int output, const char **arg)
{
	int		is_newline;
	size_t	index;

	is_newline = 1;
	index = 0;
	while (arg[index])
	{
		if (is_option(arg[index]))
			index++;
		else
			break ;
	}
	if (index != 0)
		is_newline = 0;
	while (arg[index + 1])
	{
		ft_putstr_fd((char *)arg[index], output);
		ft_putchar_fd(' ', output);
		index++;
	}
	ft_putstr_fd((char *)arg[index], output);
	return (is_newline);
}

int	execute_unset(const char **arg, t_envp **list)
{
	size_t	index;
	t_envp	*p;

	index = 0;
	while (arg[index])
	{
		p = *list;
		while (p)
		{
			if (ft_strncmp(p->variable, arg[index], \
							ft_strlen(p->variable) + 1) == 0)
				remove_env(list, p);
			p = p->next;
		}
		index++;
	}
	return (EXIT_SUCCESS);
}
