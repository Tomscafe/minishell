# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 03:19:53 by juhyelee          #+#    #+#              #
#    Updated: 2024/01/11 03:27:55 by juhyelee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFTDIR	= libft
LIBFT		= ${LIBFTDIR}/libft.a

INCS		= includes
SRCS		= srcs/execute.c
OBJS		= ${SRCS:.c=.o}

RM			= rm -rf
MK			= make -C ${LIBFTDIR}
CC			= cc
CFLAG		= -Wall -Wextra -Werror -I${INCS}
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
	${CC} ${CFLAG} $< -o $@
