/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:12:54 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/01 16:01:58 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t	preprocess(char *first_arg, int *is_newline);

int	main(int argc, char *argv[])
{
	size_t	index;
	int		is_newline;

	index = 1;
	if (argc >= 2)
		index = preprocess(argv[1], &is_newline);
	while (index  + 1 < (size_t)argc)
	{
		write(STDOUT_FILENO, argv[index], strlen(argv[index]));
		write(STDOUT_FILENO, " ", 1);
		index++;
	}
	if (index < (size_t)argc)
		write(STDOUT_FILENO, argv[index], strlen(argv[index]));
	if (is_newline)
		write(STDOUT_FILENO, "\n", 1);
	exit(EXIT_SUCCESS);
}

static size_t	preprocess(char *first_arg, int *is_newline)
{
	*is_newline = 1;
	if (strlen(first_arg) == 2 && first_arg[0] == '-')
	{
		if (first_arg[1] == 'n')
		{
			*is_newline = 0;
			return (2);
		}
		else
		{
			perror("option error");
			exit(EXIT_FAILURE);
		}
	}
	return (1);
}