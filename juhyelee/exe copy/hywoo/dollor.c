#include "minishell.h"

int	dollor_len(char *str, int k, int j)
{
	int	len;

	len = 0;
	while (str[k + len])
	{
		if (str[k + len] == ' ')
			break;
		else if (len && str[k + len] == '$')
			break;
		else if (str[k + len] == '\'')
			break;
		else if (str[k + len] == '\"')
			break;
		else if (str[k + len] == '=')
			break;
		len++;
	}
	if (k + len == j)
		return (len);
	len--;
	return (len);
}

void	dollor_dup(char *new_str, char *value, int j)
{
	int	i;

	i = 0;
	while (value[i])
	{
		new_str[j + i] = value[i];
		i++;
	}
}

char	*change_dollor(t_envp *env, char *str, int k, int r)
{
	char	*new_str;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = ft_strlen(str) - r + ft_strlen(env->value) + 1;
	new_str = malloc(sizeof(char) * size);
	while (str[j])
	{
		if (j == k)
		{
			dollor_dup(new_str, env->value, j);
			i += ft_strlen(env->value);
			j += r;
		}
		new_str[i] = str[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*check_dollor(t_token *token, char *str, int *k, int *j)
{
	t_envp	*env;
	int		i;
	int		r;

	env = token->env;
	r = dollor_len(str, *k, *j);
	while (env)
	{
		i = 0;
		while (env->variable[i] && (env->variable[i] == str[*k + i + 1]))
			i++;
		if (!env->variable[i] && (i == r - 1))
		{
			str = change_dollor(env, str, *k, r);
			*j = *j - r + ft_strlen(env->value);
			*k = *k + ft_strlen(env->value);
			return (str);
		}
		env = env->next;
	}
	return (str);
}

char	*find_dollor(t_token *token, char *str, int i, int *j)
{
	int k;

	k = i;
	while (k < *j)
	{
		if (str[k] == '\'')
			k = ignore_quotes(str, k, '\'');
		if (str[k] == '$')
			str = check_dollor(token, str, &k, j);
		k++;
	}
	return (str);
}