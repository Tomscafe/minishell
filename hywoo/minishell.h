
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define STRING 0
# define SP 1
# define QUOTE 2
# define QUOTES 3
# define DOLLOR 4
# define INPUT 5
# define OUTPUT 6
# define APPEND 7
# define PIPE 8
# define ERROR -1

// # define BACK 5
// # define SEMICOLON 4
typedef struct	s_type
{
	char			*str;
	int				type;
	struct s_type	*prev;
	struct s_type	*next;
}	t_type;

#endif