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
CFLAGS	= -Werror -Wall -Wextra
COMFILE	= -lreadline -L${HOME}/.brew/opt/readline/lib
OBFLAGS	= -I{HOME}/.brew/opt/readline/include
SRC		= main.c signal.c tokenizer.c tokenizer2.c tools.c pipe_tree.c \
		pipe_strdup.c parsing_error.c init_struct.c get_simple.c get_command.c \
		free_pipe.c envp.c dollor.c dollor2.c make_rd.c tools2.c
LIBSRC	= libft/ft_split.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_strjoin.c
OBJS	= ${SRC:.c=.o}
OBJS2	= ${LIBSRC:.c=.o}

all : ${NAME}

${NAME} : ${OBJS} ${OBJS2}
	${CC} ${CFLAGS} ${COMFILE} ${OBJS} ${OBJS2} -o ${NAME}

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
