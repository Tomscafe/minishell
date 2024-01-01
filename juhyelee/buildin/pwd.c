/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:23:49 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/01 16:36:47 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	check_option(char *first_arg);

int	main(int argc, char *argv[])
{
	char	buf[255];

	if (argc >= 2)
		check_option(argv[1]);
	if (getcwd(buf, 255) == NULL)
	{
		perror("not found path");
		exit(EXIT_FAILURE);
	}
	printf("%s\n", buf);
	exit(EXIT_SUCCESS);
}

static void	check_option(char *first_arg)
{
	if (strlen(first_arg) == 2 && first_arg[0] == '-')
	{
		perror("pwd has no option");
		exit(EXIT_FAILURE);
	}
}