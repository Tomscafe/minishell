# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 14:10:35 by juhyelee          #+#    #+#              #
#    Updated: 2024/01/10 15:33:58 by juhyelee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR	= libft
LIBFT		= ${LIBFT_DIR}/libft.a
INCS		= includes
SRCS		= srcs/execute.c \
			  srcs/env.c \
			  srcs/builtin_1.c \
			  srcs/builtin_2.c \
			  srcs/builtin_3.c \
			  srcs/builtin_4.c \
			  srcs/utils.c \
			  srcs/heredoc.c
OBJS		= ${SRCS:.c=.o}
NAME		= exe

CC			= cc
CFLAG		= -Wall -Wextra -Werror -I${INCS} -g3
LFLAG		= -lft -L${LIBFT_DIR} -lreadline

RM			= rm -rf
MK			= make -C ${LIBFT_DIR}

.PHONY : all clean fclean re

all : ${NAME}
clean : 
	${RM} ${OBJS}
	${MK} clean
fclean : clean
	${RM} ${NAME}
	${MK} fclean
re : fclean all

${NAME} : ${OBJS} ${LIBFT}
${LIBFT} :
	${MK}
%.o : %.c
	${CC} ${CFLAG} $< -o $@ -c