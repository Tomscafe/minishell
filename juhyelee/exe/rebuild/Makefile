# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 03:19:53 by juhyelee          #+#    #+#              #
#    Updated: 2024/01/17 19:28:05 by juhyelee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFTDIR	= libft
LIBFT		= ${LIBFTDIR}/libft.a

INCS		= includes
SRCS		= srcs/execute.c \
			  srcs/file_1.c \
			  srcs/file_2.c \
			  srcs/setting.c \
			  srcs/command.c \
			  srcs/child.c \
			  srcs/builtin.c \
			  srcs/echo.c \
			  srcs/cd.c \
			  srcs/export.c \
			  srcs/env.c
OBJS		= ${SRCS:.c=.o}

RM			= rm -rf
MK			= make -C ${LIBFTDIR}
CC			= cc
CFLAG		= -Wall -Wextra -Werror -I${INCS} -g3
LFLAG		= -lreadline -lft -L${LIBFTDIR}

.PHONY : all clean fclean re

all : ${OBJS} ${LIBFT}
clean :
	${RM} ${OBJS}
	${MK} clean
fclean : clean
	${MK} fclean
re : fclean all

${LIBFT} :
	${MK}
	${MK} bonus
%.o : %.c
	${CC} ${CFLAG} $< -o $@ -c