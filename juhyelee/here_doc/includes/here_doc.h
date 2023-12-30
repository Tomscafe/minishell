/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:55:23 by juhyelee          #+#    #+#             */
/*   Updated: 2023/12/30 21:10:26 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC
# define HERE_DOC

# include "../includes/libft.h"
# include <fcntl.h>
# define BUFFER_SIZE 4

int		contain_new_line(char *str);
char	*input(int fd);
char	*merge(char *s1, char *s2, size_t s2_len);
size_t	get_line_size(char *str);

#endif