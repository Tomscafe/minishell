# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 14:10:35 by juhyelee          #+#    #+#              #
#    Updated: 2024/01/10 14:18:31 by juhyelee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR	= libft
LIBFT		= ${LIBFT_DIR}/libft.a
INCS		= includes
SRCS		= srcs/execute.c \
			   srcs/env.c \
			   srcs/builtin1.c \
			   srcs/builtin2.c \
			   srcs/builtin3.c \
			   srcs/builtin4.c \
			   srcs/utils.c
OBJS		= ${SRCS:.c=.o}
NAME		= exe

CC			= cc
CFLAG		= -Wall -Wextra -Werror -I${INCS}
LFLAG		= -lft -L${LIBFT_DIR}

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
	${CC} ${LFLAG} ${OBJS} -o ${NAME}
${LIBFT} :
	${MK}
%.o : %.c
	${CC} ${CFLAG} $< -o $@