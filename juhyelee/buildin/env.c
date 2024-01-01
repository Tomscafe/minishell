/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 15:18:22 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/01 15:23:25 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int	main(int argc, char *argv[], char *envp[])
{
	size_t	index;

	if (argc != 1)
	{
		strdup(argv[0]);
		perror("env has no option an arguments");
		exit(EXIT_FAILURE);
	}
	index = 0;
	while (envp[index])
	{
		write(STDOUT_FILENO, envp[index], strlen(envp[index]));
		write(STDOUT_FILENO, "\n", 1);
		index++;
	}
	exit(EXIT_SUCCESS);
}
