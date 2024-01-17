NAME	= minishell
CC		= CC
CFLAGS	= -g3 #-fsanitize=address #-Werror -Wall -Wextra
COMFILE	= -lreadline -L/usr/local/Cellar/readline/8.2.7/lib#-L${HOME}/.brew/opt/readline/lib
OBFLAGS	= -I/usr/local/Cellar/readline/8.2.7/include #-I{HOME}/.brew/opt/readline/include
SRC		= main.c signal.c tokenizer.c init_struct.c pipe_tree.c tools.c envp.c
LIBSRC	= libft/ft_split.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_strjoin.c
OBJS	= ${SRC:.c=.o}
OBJS2	= ${LIBSRC:.c=.o}

JU_DIR = ../rebuild
EXE_DIR = ${JU_DIR}/srcs
EXE_SRCS = ${EXE_DIR}/execute.c \
		   ${EXE_DIR}/file_1.c \
		   ${EXE_DIR}/file_2.c
EXE_OBJS = ${EXE_SRCS:.c=.o}
LIBFT_DIR = ${JU_DIR}/libft
LIBFT = ${LIBFT_DIR}/libft.a
LFLAG = -lft -L${LIBFT_DIR}

all : ${NAME}

${NAME} : ${OBJS} ${OBJS2} ${EXE_OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${COMFILE} ${LFLAG} ${OBJS} ${OBJS2} ${EXE_OBJS} -o ${NAME}

.c.o:
	${CC} ${CFLAGS} ${OBFLAGS} $< -o $@ -c

clean :
	rm -rf ${OBJS} ${OBJS2}

fclean : clean
	rm -rf ${NAME}

re :
	make fclean
	make all

.PHONY : all clean fclean re