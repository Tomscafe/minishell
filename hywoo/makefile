NAME	= minishell
CC		= CC
CFLAGS	= -g3 #-fsanitize=address #-Werror -Wall -Wextra
COMFILE	= -lreadline -L${HOME}/.brew/opt/readline/lib
OBFLAGS	= -I{HOME}/.brew/opt/readline/include
SRC		= main.c signal.c tokenizer.c init_struct.c pipe_tree.c tools.c envp.c
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
