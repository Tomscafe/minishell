# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhyelee <juhyelee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/03 16:13:44 by juhyelee          #+#    #+#              #
#    Updated: 2024/01/03 21:19:05 by juhyelee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

INCS = includes
SRCS = srcs/command_1.c \
	   srcs/command_2.c \
	   srcs/option.c \
	   srcs/env.c \
	   srcs/test.c
OBJS = $(SRCS:.c=.o)
NAME= buildin

RM = rm -rf
MK = make -C

CC = cc
CFLAG = -Wall -Wextra -Werror -g3
LFLAG = -L$(LIBFTDIR) -lft

.PHONY = all clean fclean re

all : $(NAME)
clean :
	$(RM) $(OBJS)
	$(MK) $(LIBFTDIR) clean
fclean : clean
	$(RM) $(NAME)
	$(MK) $(LIBFTDIR) fclean
re : fclean all

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(LFLAG) $(OBJS) -o $(NAME)
$(LIBFT) : 
	$(MK) $(LIBFTDIR)
	$(MK) $(LIBFTDIR) bonus
%.o : %.c
	$(CC) $(CFLAG) $< -o $@ -c
