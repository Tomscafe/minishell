# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhyelee <juhyelee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 14:39:57 by juhyelee          #+#    #+#              #
#    Updated: 2024/01/09 19:53:20 by juhyelee         ###   ########.fr        #
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

JU_SRCS = srcs/execute.c \
		  srcs/env.c \
		  srcs/builtin_1.c \
		  srcs/builtin_2.c \
		  srcs/builtin_3.c \
		  srcs/builtin_4.c \
		  srcs/utils.c
JU_OBJS = ${JU_SRCS:.c=.o}
JU_LFLAG = -lft -Llibft

all : ${NAME}

${NAME} : ${OBJS} ${OBJS2} $(JU_OBJS)
	${CC} ${CFLAGS} ${JU_LFLAG}${COMFILE} ${OBJS} ${OBJS2} -o ${NAME}

.c.o:
	${CC} ${CFLAGS} ${OBFLAGS} -c $< -o $@

clean :
	rm -rf ${OBJS} ${OBJS2}

fclean : clean
	rm -rf ${NAME}

re :
	make fclean
	make all

.PHONY : all clean fclean re
