/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hywoo <hywoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:46:06 by hywoo             #+#    #+#             */
/*   Updated: 2024/01/14 14:46:42 by hywoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../includes/minishell2.h"

void	ft_parsing(char *str, t_envp *env)
{
	t_token	*token;
	t_pipe	*pipe_tree;

	if (valid_quotes(str))
		return ;
	token = init_token(NULL);
	token->env = env;
	tokenizer(token, str);
	if (syntax_error(token))
	{
		all_free(token, NULL);
		return ;
	}
	pipe_tree = make_pipe_tree(NULL, NULL, token->next, 0);
	execute(pipe_tree, &env);
	all_free(token, pipe_tree);
}

void	input_sigterm(void)
{
	printf("\033[1A");
	printf("\033[10C");
	printf(" exit\n");
	exit(-1);
}

void	ft_readline(t_envp *env)
{
	char	*str;

	while (1)
	{
		str = readline("minishell$ ");
		if (str && !*str)
		{
			free (str);
			str = NULL;
		}
		else if (str)
		{
			add_history(str);
			ft_parsing(str, env);
			free (str);
			str = NULL;
		}
		else if (!str)
			input_sigterm();
		else if (*str == '\0')
			free (str);
	}
}

int	main(int ac, char **av, char *envp[])
{
	t_envp	*env;

	env = make_env(envp);
	(void)av;
	if (ac != 1)
	{
		printf("error\n");
		return (2);
	}
	ft_signal();
	ft_readline(env);
	return (0);
}
