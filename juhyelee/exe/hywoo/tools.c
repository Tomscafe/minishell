#include "minishell.h"

void	test_envp(t_envp *env)
{
	while (env)
	{
		printf("%s=%s\n", env->variable, env->value);
		env = env->next;
	}
}

void	test_token(t_token *token)
{
	while (token)
	{
		printf("type:%d + %s\n", token->type, token->str);
		token = token->next;
	}
}

void	test_redirection(t_pipe *pipe, int i)
{
	t_redirection	*rd;

	if (i == 1)
	{
		if (!pipe->first){
			printf("\n");
			return;}
		rd = pipe->first->redirection;
	}
	else if (i == 2)
	{
		if (!pipe->second){
			printf("\n");
			return;}
		rd = pipe->second->redirection;
	}
	while (rd)
	{
		printf("\033[0;33m(rd)\033[0m");
		printf("\033[0;36m%s %s\033[0m", rd->symbol, rd->file);
		rd = rd->next;
	}
	printf("\n");
}

void	test_pipe(t_pipe *pipe)
{
	char	*com1;
	char	*com2;
	char	*first;
	char	*second;
	int		i = 1;

	while (pipe)
	{
		com1 = pipe->first->simple_command->command;
		first = pipe->first->simple_command->ward;
		if (pipe->second)
		{
			com2 = pipe->second->simple_command->command;
			second = pipe->second->simple_command->ward;
		}
		else {
			com2 = NULL;
			second = NULL;
		}
		printf("\033[0;32mPIPE %d: \033[0m", i);
		printf("\033[0;34mfirst\033[0m");
		printf("\033[0;33m(com)\033[0m");
		printf("\033[0;34m%s \033[0m", com1);
		printf("\033[0;33m(ward)\033[0m");
		printf("\033[0;34m%s\033[0m", first);
		test_redirection(pipe, 1);
		printf("\033[0;32m      : \033[0m");
		printf("\033[0;35msecond\033[0m");
		printf("\033[0;33m(com)\033[0m");
		printf("\033[0;35m%s \033[0m", com2);
		printf("\033[0;33m(ward)\033[0m");
		printf("\033[0;35m%s\033[0m", second);
		test_redirection(pipe, 2);
		pipe = pipe->next;
		i++;
	}
}

int	valid_redirection(t_token *curr)
{
	if (curr->type != REDIRECTION)
		return (0);
	if (ft_strlen(curr->str) > 1)
	{
		if (curr->str[0] != curr->str[1])
		{
			if (curr->next)
			{
				if (curr->next->type == REDIRECTION && curr->next->str)
				{
					if (curr->str[1] == curr->next->str[0])
					{
						printf("syntax error near unexpected token `%c%c'\n", curr->str[1], curr->str[1]);
						return (2);
					}
				}
			}
			printf("syntax error near unexpected token `%c'\n", curr->str[1]);
			return (2);
		}
	}
	if (!curr->next)
	{
		printf("syntax error near unexpected token `newline'\n");
		return (2);
	}
	if (curr->next->type == REDIRECTION || curr->next->type == PIPE)
	{
		printf("syntax error near unexpected token `%s'\n", curr->next->str);
		return (2);
	}
	if (curr->next->type != WARD)
	{
		printf("syntax error near unexpected token `newline'\n");
		return (2);
	}
	return (0);
}

int	valid_pipe(t_token *curr)
{
	int	flag;

	flag = 0;
	if (curr->type != PIPE)
		return (0);
	if (curr->next)
	{
		if (curr->next->type == PIPE)
		{
			printf("bash: syntax error near unexpected token `|'\n");
			return (1);
		}
	}
	else {
		printf("bash: syntax error: unexpected end of file\n");
		return (1);	//input pipe?
	}
	return (0);
}

int	syntax_error(t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr)
	{
		if (valid_redirection(curr))
			return (1);
		else if (valid_pipe(curr))
			return (1);
		curr = curr->next;
	}
	return (0);
}

void	free_command(t_command *com)
{
	t_redirection	*curr_rd;
	t_redirection	*next_rd;

	if (com->simple_command)
	{
		if (com->simple_command->command)
			free (com->simple_command->command);
		if (com->simple_command->ward)
			free (com->simple_command->ward);
		free (com->simple_command);
	}
	if (com->redirection)
	{
		curr_rd = com->redirection;
		while (curr_rd)
		{
			next_rd = curr_rd->next;
			if (curr_rd->symbol)
				free(curr_rd->symbol);
			if (curr_rd->file)
				free(curr_rd->file);
			free (curr_rd);
			curr_rd = next_rd;
		}
	}
	free(com);
}

void	all_free(t_token *token, t_pipe *pipe)
{
	t_token	*token_next;
	t_pipe	*pipe_next;

	token_next = token;
	pipe_next = pipe;
	if (token)
	{
		while (token)
		{
			token_next = token->next;
			if (token->str)
				free(token->str);
			free(token);
			token = token_next;
		}
	}
	if (pipe)
	{
		while (pipe)
		{
			pipe_next = pipe->next;
			if (pipe->first)
				free_command(pipe->first);
			if (pipe->second)
			{
				free_command(pipe->second);
				if (pipe_next)
					pipe_next->first = NULL;
			}
			free (pipe);
			pipe = pipe_next;
		}
	}
}
