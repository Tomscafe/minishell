# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/28 21:05:25 by juhyelee          #+#    #+#              #
#    Updated: 2023/12/28 21:51:40 by juhyelee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFTDIR=libft
LIBFT=$(LIBFTDIR)/libft.a

INCS=includes
SRCS=srcs/main.c \
	 srcs/parse.c \
	 srcs/execute.c
OBJS=$(SRCS:.c=.o)
NAME=pipex

RM=rm -rf
MK=make -C

CC=cc
CFLAG=-Wall -Wextra -Werror
LFLAG=-L$(LIBFTDIR) -lft

.PHONY=all clean fclean re

all: $(NAME)
clean:
	$(RM) $(OBJS)
	$(MK) $(LIBFTDIR) clean
fclean: clean
	$(RM) $(NAME)
	$(MK) $(LIBFTDIR) fclean
re: fclean all

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(LFLAG) $(OBJS) -o $(NAME)
$(LIBFT):
	$(MK) $(LIBFTDIR)
%.o: %.c
	$(CC) $(CFLAG) $< -o $@ -c