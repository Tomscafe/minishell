/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 09:07:15 by juhyelee          #+#    #+#             */
/*   Updated: 2023/12/30 09:53:49 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_proc	proc;
	t_list	*cmd;
	size_t	index;

	set_proc(argc, argv, envp, &proc);
	cmd = proc.clist;
	index = 0;
	while (cmd)
	{
		execute_command(cmd, &proc, index);
		cmd = cmd->next;
		index++;
	}
	exit(EXIT_SUCCESS);
}

void	set_proc(int argc, char *argv[], char *envp[], t_proc *proc)
{
	if (argc < 5)
	{
		perror("need more arguments");
		exit(EXIT_FAILURE);
	}
	pipe(proc->pipefd);
	proc->infd = open(argv[1], O_RDONLY);
	if (proc->infd == -1)
	{
		perror("fail to open infile");
		exit(EXIT_FAILURE);
	}
	proc->outfd = \
			open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (proc->outfd == -1)
	{
		perror("fail to open outfile");
		exit(EXIT_FAILURE);
	}
	proc->envp = envp;
	proc->path = set_path(envp);
	proc->clist = NULL;
	set_commands(argc, argv, &proc->clist);
}

void	set_commands(int argc, char *argv[], t_list **clist)
{
	int		index;
	char	**cmd;
	t_list	*new_cmd;

	index = 2;
	while (index + 1 < argc)
	{
		cmd = ft_split(argv[index], ' ');
		if (!cmd)
		{
			perror("fail to split command");
			exit(EXIT_FAILURE);
		}
		new_cmd = ft_lstnew(cmd);
		if (!new_cmd)
		{
			perror("fail to create new node");
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back(clist, new_cmd);
		index++;
	}
}

char	**set_path(char *envp[])
{
	char	**path;
	size_t	index;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp("PATH", envp[index], 4) == 0)
		{
			path = ft_split(envp[index] + 5, ':');
			if (!path)
			{
				perror("fail to split path");
				exit(EXIT_FAILURE);
			}
			return (path);
		}
		index++;
	}
	perror("not found path");
	exit(EXIT_FAILURE);
}

char	*merge(char *s1, char *s2)
{
	int		size;
	char	*ret;

	size = ft_strlen(s1) + ft_strlen(s2) + 2;
	ret = (char *)malloc(sizeof(char) * size);
	if (!ret)
	{
		perror("fail to merge");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(ret, s1, size);
	ft_strlcat(ret, "/", size);
	ft_strlcat(ret, s2, size);
	return (ret);
}