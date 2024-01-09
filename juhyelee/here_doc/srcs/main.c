/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 20:30:28 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/04 15:14:22 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/here_doc.h"

int	main(void)
{
	pid_t		child;
	const int	file = open("hd", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	heredoc("end", file);
	child = fork();
	if (child == 0)
		execl("/bin/cat", "cat", "hd", NULL);
	wait(NULL);
	close(file);
	unlink("hd");
	return (0);
}
