# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhyelee <juhyelee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 14:39:57 by juhyelee          #+#    #+#              #
#    Updated: 2024/01/09 20:07:03 by juhyelee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= CC
CFLAGS	= -g3 #-fsanitize=address #-Werror -Wall -Wextra
COMFILE	= -lreadline -L${HOME}/.brew/opt/readline/lib
OBFLAGS	= -I{HOME}/.brew/opt/readline/include
SRC		= main.c signal.c tokenizer.c init_struct.c pipe_tree.c tools.c envp.c
LIBSRC	= libft/ft_split.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_strjoin.c
OBJS	= ${SRC:.c=.o}
OBJS2	= ${LIBSRC:.c=.o}

## JUHYELEE
JU_INCS = includes
JU_LIBFTDIR = libft
JU_LIBFT = ${JU_LIBFTDIR}/libft.a
JU_SRCS = srcs/execute.c \
		  srcs/env.c \
		  srcs/builtin_1.c \
		  srcs/builtin_2.c \
		  srcs/builtin_3.c \
		  srcs/builtin_4.c \
		  srcs/utils.c
JU_OBJS = ${JU_SRCS:.c=.o}
JU_LFLAG = -lft -L${JU_LIBFTDIR} -I${JU_INCS}

all : ${NAME}

${NAME} : ${OBJS} ${OBJS2} ${JU_OBJS} ${JU_LIBFT}
	${CC} ${CFLAGS} ${JU_LFLAG} ${COMFILE} ${OBJS} ${OBJS2} -o ${NAME}

.c.o:
	${CC} ${CFLAGS} ${OBFLAGS} -c $< -o $@

clean :
	rm -rf ${OBJS} ${OBJS2} ${JU_OBJS}

fclean : clean
	rm -rf ${NAME}

re :
	make fclean
	make all

.PHONY : all clean fclean re

##JUHYELEE
${JU_LIBFT}:
	make -C ${JU_LIBFTDIR}