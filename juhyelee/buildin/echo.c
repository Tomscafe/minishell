/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:12:54 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/01 15:15:10 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(int argc, char *argv[])
{
	size_t	index;

	index = 1;
	while (index < (size_t)argc)
	{
		if (strlen(argv[index]) == 2 && argv[index][0] == '-')
		{
			perror("echo does not have option");
			exit(EXIT_FAILURE);
		}
		index++;
	}
	index = 1;
	while (index < (size_t)argc)
	{
		write(STDOUT_FILENO, argv[index], strlen(argv[index]));
		write(STDOUT_FILENO, " ", 1);
		index++;
	}
	write(STDOUT_FILENO, "\n", 1);
	exit(EXIT_SUCCESS);
}