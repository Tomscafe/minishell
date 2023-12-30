/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 20:30:28 by juhyelee          #+#    #+#             */
/*   Updated: 2023/12/30 21:13:08 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/here_doc.h"

int	main(int argc, char *argv[])
{
	int		file;
	char	*input_str;

	file = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	input_str = input(STDIN_FILENO);
	ft_putendl_fd(input_str, file);
	while (ft_strncmp(input_str, argv[1], ft_strlen(input_str)))
	{
		free(input_str);
		input_str = input(STDIN_FILENO);
		ft_putendl_fd(input_str, file);
	}
	free(input_str);
	close(file);
	return (argc);
}