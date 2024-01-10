NAME	= minishell
CC		= CC
CFLAGS	= -g3 #-fsanitize=address #-Werror -Wall -Wextra
COMFILE	= -lreadline -L${HOME}/.brew/opt/readline/lib
OBFLAGS	= -I{HOME}/.brew/opt/readline/include
SRC		= main.c signal.c tokenizer.c init_struct.c pipe_tree.c tools.c envp.c
LIBSRC	= libft/ft_split.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_strjoin.c
OBJS	= ${SRC:.c=.o}
OBJS2	= ${LIBSRC:.c=.o}

EXE_DIR = ../juhyelee/srcs
EXE_SRCS = ${EXE_DIR}/execute.c \
		   ${EXE_DIR}/env.c \
		   ${EXE_DIR}/utils.c \
		   ${EXE_DIR}/heredoc.c \
		   ${EXE_DIR}/builtin_1.c \
		   ${EXE_DIR}/builtin_2.c \
		   ${EXE_DIR}/builtin_3.c \
		   ${EXE_DIR}/builtin_4.c
EXE_OBJS = ${EXE_SRCS:.c=.o}
LIBFT_DIR = ../juhyelee/libft
LIBFT = ${LIBFT_DIR}/libft.a
LFLAG = -lft -L${LIBFT_DIR}

all : ${NAME}

${NAME} : ${OBJS} ${OBJS2} ${EXE_OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${COMFILE} ${LFLAG} ${OBJS} ${OBJS2} ${EXE_OBJS} -o ${NAME}

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
