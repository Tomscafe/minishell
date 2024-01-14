#include "../minishell.h"

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
