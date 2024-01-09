/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:24:08 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/03 21:36:47 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buildin.h"

int	echo_cmd(const size_t argc, const char *argv[])
{
	int		is_newline;
	size_t	index;

	close(STDIN_FILENO);
	is_newline = 1;
	if (argc > 1)
			is_newline = check_echo_option(argv[1]);
	index = 1;
	if (is_newline == 0)
		index++;
	while (index + 1 < argc)
	{
		printf("%s ", argv[index]);
		index++;
	}
	if (index < argc)
		printf("%s", argv[index]);
	if (is_newline)
		printf("\n");
	return (0);
}

int	cd_cmd(const size_t argc, const char *argv[])
{
	close(STDIN_FILENO);
	if (argc == 1)
		chdir("~");
	else if (chdir(argv[1]) == -1)
	{
		print_error("cd", "No such file or directory", argv[1]);
		return (FAIL);
	}
	return (0);
}

int	exit_cmd(const size_t argc, const char *argv[])
{
	int	exit_num;

	if (argc > 2)
	{
		print_error("exit", "too many arguments", "");
		return (1);
	}
	if (argc == 1)
		exit_num = 0;
	else
		exit_num = ft_atoi(argv[1]);
	exit(exit_num);
}

void	pwd_cmd(void)
{
	char	buffer[BUFFER_SIZE];

	close(STDIN_FILENO);
	getcwd(buffer, BUFFER_SIZE);
	printf("%s\n", buffer);
}
