/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:36:04 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/18 12:40:54 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_at_child(t_proc proc, t_exe *exe, int *pipefd)
{
	const char	**env = (const char **)convert_to_array(*exe->env);
	const char	**arg = (const char **)ft_split(proc.arg, ' ');
	char		*path;

	signal(SIGINT, SIG_DFL);
	path = is_executable(proc.cmd, env);
	if (!path)
	{
		printf("minishell: %s: Not found command\n", proc.cmd);
		exit(EXIT_FAILURE);
	}
	apply_redir(proc, pipefd, exe->p_pipe);
	execve(path, (char *const *)arg, (char *const *)env);
	clear_strs((char **)env);
	clear_strs((char **)arg);
	free(path);
}

void	apply_redir(t_proc proc, int *pipefd, int prev)
{
	if (proc.input != STDIN_FILENO)
	{
		dup2(proc.input, STDIN_FILENO);
		close(proc.input);
	}
	if (proc.output != STDOUT_FILENO)
	{
		dup2(proc.output, STDOUT_FILENO);
		close(proc.output);
	}
	if (pipefd)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

char	*is_executable(const char *cmd, const char **env)
{
	if (cmd[0] == '.')
		return (user_command(cmd + 1));
	return (other_builtin(cmd, env));
}

char	*user_command(const char *cmd)
{
	char	buffer[2024];
	char	*pwd;
	char	*ret;

	if (!getcwd(buffer, 2024))
		return (NULL);
	pwd = ft_strjoin(buffer, "/");
	if (!pwd)
		exit(EXIT_FAILURE);
	ret = ft_strjoin(pwd, cmd);
	if (!ret)
		exit(EXIT_FAILURE);
	return (ret);
}

char	*other_builtin(const char *cmd, const char **env)
{
	size_t	index;
	char	**path;
	char	*ret;

	path = get_paths(env);
	index = 0;
	while (path[index])
	{
		ret = get_exe_path(path[index], cmd);
		if (access(ret, X_OK) == 0)
			return (ret);
		index++;
		free(ret);
	}
	clear_strs(path);
	return (NULL);
}
