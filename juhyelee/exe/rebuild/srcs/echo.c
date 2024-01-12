/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:21:41 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/12 12:54:27 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_echo(t_table table, const int n_exit)
{
	pid_t	child;
	int		is_newline;
	int		exit_num;

	child = fork();
	if (child < 0)
		exit(EXIT_FAILURE);
	else if (child == 0)
	{
		builtin_output(table.input, table.output);
		table.argument += 5;
		is_newline = get_echo_option(table.argument);
		if (is_newline < 0)
			exit(EXIT_FAILURE);
		else if (!is_newline)
			table.argument += 2;
		if (table.argument[0] == ' ')
			table.argument++;
		print_arg(table.argument, n_exit);
		if (is_newline)
			write(STDOUT_FILENO, "\n", 1);
		exit(EXIT_SUCCESS);
	}
	waitpid(child, &exit_num, WUNTRACED);
	return (WEXITSTATUS(exit));
}

int	get_echo_option(const char *arg)
{
	char	option[4];

	if (arg[0] == '\0')
		return (1);
	ft_memset(option, 0, 4);
	ft_strlcpy(option, arg, 4);
	if (option[0] == '-')
	{
		if (option[1] == 'n')
		{
			if (option[2] == ' ' || option[2] == '\0')
				return (0);
			else
				return (1);
		}
		else if (option[2] == ' ' || option[2] == '\0')
		{
			printf("minishell: echo: Invalid option\n");
			return (-1);
		}
	}
	return (1);
}

void	print_arg(const char *str, const int n_exit)
{
	size_t	index;

	index = 0;
	while (str[index + 1])
	{
		if (str[index] == '$' && str[index + 1] == '?')
		{
			ft_putnbr_fd(n_exit, STDOUT_FILENO);
			index++;
		}
		ft_putchar_fd(str[index], STDOUT_FILENO);
		index++;
	}
	ft_putchar_fd(str[index], STDOUT_FILENO);
}
