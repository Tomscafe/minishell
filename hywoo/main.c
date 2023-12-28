#include "minishell.h"

t_pipe	*init_pipe(t_pipe *pipe)
{
	pipe = malloc(sizeof(t_pipe));
	if (!pipe)
		exit (-1);
	pipe->first = NULL;
	pipe->second = NULL;
	pipe->next = NULL;
	return (pipe);
}

t_command	*init_com(t_command *com)
{
	com = malloc(sizeof(t_command));
	if (!com)
		exit (-1);
	com->redirection = NULL;
	com->simple_command = NULL;
	return (com);
}

t_redirection	*init_redirection(t_redirection *rd)
{
	rd = malloc(sizeof(t_redirection));
	if (!rd)
		exit (-1);
	rd->symbol = NULL;
	rd->file = NULL;
	rd->next = NULL;
	return (rd);
}

t_simple	*make_simple_command(t_token *front, t_command *com)
{
	t_simple	*simple;

	simple = malloc(sizeof(t_simple));
	if (!simple)
		exit (-1);
	if (front->type == COMMAND)
		simple->command = ft_strdup(front->str);
	if (front->next)
	{
		if (front->next->type == WARD)
			simple->ward = ft_strdup(front->next->str);
	}
	return (simple);
}

t_token	*add_back_rd(t_token *curr, t_redirection *rd)
{
	t_redirection	*new;

	new = init_redirection(new);
	new->symbol = ft_strdup(curr->str);
	curr = curr->next;
	if (curr->type == WARD)
		new->file = ft_strdup(curr->str);
	rd->next = new;
	curr = curr->next;
	return (curr);
}

t_redirection	*make_redirection(t_token *front, t_command *com)
{
	t_redirection	*rd;
	t_redirection	*head;
	t_token			*curr;

	curr = front;
	rd = init_redirection(rd);
	while (curr)
	{
		if (curr->type == REDIRECTION)
			curr = add_back_rd(curr, rd);
		if (curr->type == PIPE)
			break;
		curr = curr->next;
	}
	head = rd;
	rd = rd->next;
	free (head);
	return (rd);
}

t_command	*make_command(t_token *front)
{
	t_command	*com;

	com = init_com(com);
	com->simple_command = make_simple_command(front, com);
	com->redirection = make_redirection(front, com);
	return (com);
}

t_token	*find_next_front(t_token *front)
{
	while (front)
	{
		front = front->next;
		if (front->type == PIPE)
		{
			front = front->next;
			break;
		}
	}
	return (front);
}

t_pipe	*new_pipe(t_pipe *pipe, t_token *front)
{
	t_pipe	*new;

	if (!pipe->first)
	{
		pipe->first = make_command(front);
		return (pipe);
	}
	if (!pipe->second)
	{
		pipe->second = make_command(front);
		return (pipe);
	}
	new = init_pipe(pipe);
	new->first = pipe->second;
	new->second = make_command(front);
	pipe->next = new;
	return (new);
}

t_pipe	*make_pipe_tree(t_pipe *pipe, t_token *token)
{
	t_token	*front;
	t_token	*curr;
	t_pipe	*next_pipe;
	int		cnt;

	pipe = init_pipe(pipe);
	front = token;
	curr = token;
	next_pipe = pipe;
	cnt = 0;
	while (curr)
	{
		if (curr->type == PIPE)
		{
			curr = curr->next;
			next_pipe = new_pipe(pipe, front);
			front = find_next_front(front);
			cnt++;
		}
		curr = curr->next;
	}
	if (!cnt)
		pipe->first = make_command(front);
	printf("token:%s\n", front->str);
	// printf("%s\n",pipe->first->simple_command->command);
	// else
	// 	next_pipe->second = make_command(front);
	return (pipe);
}

void	test_token(t_token *token)
{
	while (token)
	{
		printf("type:%d + %s\n", token->type, token->str);
		token = token->next;
	}
}

void	test_pipe(t_pipe *pipe)
{
	char	*com;
	char	*ward;

	com = pipe->first->simple_command->command;
	ward = pipe->first->simple_command->ward;
	while (pipe)
	{
		printf("COM:%s WARD:%s\n", com, ward);
		pipe = pipe->next;
	}
}

void	ft_parsing(char *str)
{
	t_token	*token;
	t_pipe	*pipe_tree;

	if (valid_quotes(str))
		return ;
	token = init_token(token);
	tokenizer(token, str);
	pipe_tree = make_pipe_tree(pipe_tree, token->next);
	// test_token(token);
	// test_pipe(pipe_tree);
}

void	ft_readline(void)
{
	char	*str;

	while (1)
	{
		str = readline("minishell$ ");
		if (str)
		{
			add_history(str);
			ft_parsing(str);
			free (str);
			str = NULL;
		}
		else if (!str)
		{
			printf("\033[1A");
			printf("\033[10C");
			printf(" exit\n");
			exit(-1);
		}
		else if (*str == '\0')
			free (str);
	}
}

int	main(int ac, char **av, char *envp[])
{
	if (ac != 1)
	{
		printf("error\n");
		return (2);
	}
	ft_signal();
	ft_readline();
	return (0);
}