/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:21:41 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/18 14:29:40 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_echo(t_proc proc, const char **arg, const int n_exit)
{
	pid_t	child;
	size_t	index;
	int		is_newline;
	int		exit_num;

	child = fork();
	if (child < 0)
		exit(EXIT_FAILURE);
	else if (child == 0)
	{
		index = 0;
		if (!arg[0])
			write(proc.output, "\n", 1);
		is_newline = get_echo_option(arg[0]);
		if (is_newline < 0)
			exit(EXIT_FAILURE);
		else if (!is_newline)
			index++;
		print_arg(arg + index, proc.output, n_exit);
		if (is_newline)
			write(proc.output, "\n", 1);
		exit(EXIT_SUCCESS);
	}
	waitpid(child, &exit_num, WUNTRACED);
	return (WEXITSTATUS(exit_num));
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

void	print_arg(const char **arg, const int output, const int n_exit)
{
	size_t	index;

	index = 0;
	while (arg[index + 1])
	{
		print_str(arg[index], output, n_exit);
		write(output, " ", 1);
		index++;
	}
	print_str(arg[index], output, n_exit);
}

void	print_str(const char *str, const int output, const int n_exit)
{
	size_t	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == '$')
		{
			index++;
			continue ;
		}
		if (str[index - 1] == '$' && str[index] == '?')
		{
			ft_putnbr_fd(n_exit, output);
			index += 2;
		}
		write(output, str + index, 1);
		index++;
	}
	write(output, str + index, 1);
}

int	execute_unset(const char **arg, t_envp **list)
{
	size_t	index;
	t_envp	*p;

	if (!arg[0])
		return (EXIT_SUCCESS);
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
