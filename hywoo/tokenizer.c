#include "minishell.h"

int	valid_quotes(char *str)
{
	int	i;
	int	flag1;
	int	flag2;

	i = 0;
	flag1 = 0;
	flag2 = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			flag1++;
		if (str[i] == '\"')
			flag2++;
		i++;
	}
	if (flag1 % 2 || flag2 % 2)
	{
		printf("minishell: syntax error\n");
		return (1);
	}
	return (0);
}

int	check_type(char c)
{
	if (c == '\'')
		return (QUOTE);
	if (c == '\"')
		return (QUOTES);
	if (c == '>' || c == '<')
		return (REDIRECTION);
	if (c == '|')
		return (PIPE);
	if (c == ' ')
		return (SP);
	return (WARD);
}

t_token	*init_token(t_token *token)
{
	token = malloc(sizeof(t_token));
	if (!token)
		exit (-1);
	token->str = NULL;
	token->type = 0;
	token->next = NULL;
	return (token);
}

void	add_token_back(t_token *token, char *str, int type)
{
	t_token	*new;

	new = init_token(new);
	new->str = str;
	new->type = type;
	while (token->next)
		token = token->next;
	token->next = new;
}

int	ignore_space(char *str, int i, int type)
{
	if (type != SP)
		return (i);
	while (str[i] == ' ')
		i++;
	return (i);
}

int	ignore_quotes(char *str, int j, char c)
{
	if (str[j] == c)
		j++;
	while (str[j] != c)
		j++;
	return (j);
}

int	token_command(t_token *token, char *str, int i, int type)
{
	int		j;
	char	*command;

	if (type == SP || type == PIPE || type == REDIRECTION)
		return (i);
	j = i;
	while (str[j] && str[j] != ' ')
	{
		type = check_type(str[j]);
		if (str[j] == '\'')
			j = ignore_quotes(str, j, '\'');
		if (str[j] == '\"')
			j = ignore_quotes(str, j, '\"');
		if (type == PIPE || type == REDIRECTION)
			break;
		j++;
	}
	// str = find_dollor(token, str, i, &j);
	command = mini_strdup(str, i, j);
	add_token_back(token, command, COMMAND);
	return (j);
}

int	end_of_ward(char c)
{
	int	type;

	type = check_type(c);
	if (type == REDIRECTION)
		return (1);
	if (type == PIPE)
		return (1);
	return (0);
}

int	token_ward(t_token *token, char *str, int i, int type)
{
	int		j;
	char	*ward;

	if (type == SP || type == PIPE || type == REDIRECTION)
		return (i);
	j = i;
	while (str[j])
	{
		if (str[j] == '\'')
			j = ignore_quotes(str, j, '\'');
		if (str[j] == '\"')
			j = ignore_quotes(str, j, '\"');
		if (end_of_ward(str[j]))
			break;
		j++;
	}
	ward = mini_strdup(str, i, j);
	add_token_back(token, ward, WARD);
	return (j);
}

int	token_redirection(t_token *token, char *str, int i, int type)
{
	int		j;
	char	*redirection;

	j = i;
	if (type != REDIRECTION)
		return (i);
	if (str[i + 1] == '>' || str[i + 1] == '<')
		j++;
	j++;
	redirection = mini_strdup(str, i, j);
	add_token_back(token, redirection, REDIRECTION);
	return (j);
}

int	token_pipe(t_token *token, char *str, int i, int type)
{
	int		j;
	char	*pipe;

	j = i;
	if (type != PIPE)
		return (i);
	j++;
	pipe = mini_strdup(str, i, j);
	add_token_back(token, pipe, PIPE);
	return (j);
}

int	token_flag(t_token *token)
{
	while (token->next)
		token = token->next;
	if (token->type == PIPE)
		return (1);
	else
		return (0);
}

void	tokenizer(t_token *token, char *str)
{
	int	i;
	int	type;
	int	flag;

	i = 0;
	flag = 1;
	while (str[i])
	{
		i = ignore_space(str, i, check_type(str[i]));
		type = check_type(str[i]);
		if (flag)
			i = token_command(token, str, i, type);
		else
			i = token_ward(token, str, i, type);
		type = check_type(str[i]);
		i = token_redirection(token, str, i, type);
		i = token_pipe(token, str, i, type);
		flag = token_flag(token);
	}
}
