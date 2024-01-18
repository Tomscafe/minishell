# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/17 20:33:57 by juhyelee          #+#    #+#              #
#    Updated: 2024/01/17 20:33:58 by juhyelee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= CC
CFLAGS	= -Werror -Wall -Wextra -g3
COMFILE	= -lreadline -L${HOME}/.brew/opt/readline/lib
OBFLAGS	= -I{HOME}/.brew/opt/readline/include
SRC		= SRC1/main.c SRC1/signal.c SRC1/tokenizer.c SRC1/tokenizer2.c SRC1/tools.c SRC1/pipe_tree.c \
		SRC1/pipe_strdup.c SRC1/parsing_error.c SRC1/init_struct.c SRC1/get_simple.c SRC1/get_command.c \
		SRC1/free_pipe.c SRC1/envp.c SRC1/dollor.c SRC1/dollor2.c SRC1/make_rd.c SRC1/tools2.c SRC1/test.c
SRC2	= SRC2/builtin.c SRC2/cd.c SRC2/child.c SRC2/command.c SRC2/echo.c SRC2/env.c \
		SRC2/execute.c SRC2/export.c SRC2/file_1.c SRC2/file_2.c SRC2/setting.c
LIBSRC	= libft/ft_isascii.c libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c \
		libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isprint.c libft/ft_itoa.c libft/ft_memchr.c \
		libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memset.c libft/ft_putchar_fd.c \
		libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_split.c libft/ft_strchr.c \
		libft/ft_strdup.c libft/ft_striteri.c libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c \
		libft/ft_strlen.c libft/ft_strmapi.c libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c \
		libft/ft_strtrim.c libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c \
		libft/ft_lstadd_back.c libft/ft_lstadd_front.c libft/ft_lstclear.c libft/ft_lstdelone.c \
		libft/ft_lstiter.c libft/ft_lstlast.c libft/ft_lstmap.c libft/ft_lstnew.c libft/ft_lstsize.c
OBJS	= ${SRC:.c=.o}
OBJS2	= ${LIBSRC:.c=.o}
OBJS3	= ${SRC2:.c=.o}

all : ${NAME}

${NAME} : ${OBJS} ${OBJS2} ${OBJS3}
	${CC} ${CFLAGS} ${COMFILE} ${OBJS} ${OBJS2} ${OBJS3} -o ${NAME}

.c.o:
	${CC} ${CFLAGS} ${OBFLAGS} -c $< -o $@

clean :
	rm -rf ${OBJS} ${OBJS2} ${OBJS3}

fclean : clean
	rm -rf ${NAME}

re :
	make fclean
	make all

.PHONY : all clean fclean re
