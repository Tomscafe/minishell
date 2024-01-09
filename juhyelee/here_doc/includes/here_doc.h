/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:55:23 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/04 14:48:16 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "../includes/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# define BUFFER_SIZE 4

void	heredoc(const char *end_str, const int output);

int		contain_new_line(char *str);
char	*input(int fd);
char	*merge(char *s1, char *s2, size_t s2_len);
char	*check_remain(char *remain);
size_t	get_line_size(char *str);

#endif