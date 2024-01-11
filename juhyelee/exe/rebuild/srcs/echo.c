/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:21:41 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/11 15:52:17 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_echo(const char *arg, const int n_exit)
{
	int	is_newline;

	arg += 5;
	is_newline = get_echo_option(arg);
	if (is_newline < 0)
		return (EXIT_FAILURE);
	else if (!is_newline)
		arg += 2;
	if (arg[0])
		print_arg(arg + 1, n_exit);
	if (is_newline)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}

int	get_echo_option(const char *arg)
{
	char	option[4];
	int		is_same_option;
	int		is_not_same_option;

	if (arg[0] == '\0')
		return (1);
	ft_memset(option, 0, 4);
	ft_strlcpy(option, arg, 4);
	is_same_option = (option[0] == '-' && option[1] == 'n');
	is_not_same_option = (option[0] == '-' && option[1] != 'n');
	if (is_same_option && option[2] != '\0' && option[2] == ' ')
		return (1);
	if (is_same_option && (option[2] == '\0' || option[2] == ' '))
		return (0);
	if (is_not_same_option && option[2] != '\0' && option[2] != ' ')
		return (1);
	if (is_not_same_option && (option[2] == '0' || option[2] == ' '))
	{
		printf("minishell: echo: Invalid option\n");
		return (-1);
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
