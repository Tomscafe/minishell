# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 03:19:53 by juhyelee          #+#    #+#              #
#    Updated: 2024/01/11 18:42:28 by juhyelee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFTDIR	= libft
LIBFT		= ${LIBFTDIR}/libft.a

INCS		= includes
SRCS		= srcs/execute.c \
			  srcs/child.c \
			  srcs/over.c \
			  srcs/table.c \
			  srcs/builtin.c \
			  srcs/heredoc.c \
			  srcs/env.c \
			  srcs/echo.c \
			  srcs/cd.c \
			  srcs/pwd.c \
			  srcs/export_1.c \
			  srcs/export_2.c \
			  srcs/unset.c \
			  srcs/exit.c
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
%.o : %.c
	${CC} ${CFLAG} $< -o $@ -c
