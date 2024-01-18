/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:39:21 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/17 20:05:05 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell2.h"

void	add_input(t_list **files, const char *file_name)
{
	t_file	*infile;
	t_list	*new_el;

	infile = (t_file *)malloc(sizeof(t_file));
	if (!infile)
		exit(EXIT_FAILURE);
	if (is_exist((const t_list *)(*files), file_name))
		return ;
	infile->name = (char *)file_name;
	infile->io[WRITE] = 0;
	infile->io[READ] = open(file_name, O_RDONLY);
	if (infile->io[READ] < 0)
	{
		free(infile);
		return ;
	}
	new_el = ft_lstnew(infile);
	if (!new_el)
		exit(EXIT_FAILURE);
	ft_lstadd_back(files, new_el);
}

void	add_output(t_list **files, char *file_name, const int mode)
{
	t_file	*outfile;
	t_list	*new_el;

	outfile = (t_file *)malloc(sizeof(t_file));
	if (!outfile)
		exit(EXIT_FAILURE);
	if (is_exist((const t_list *)(*files), file_name))
		return ;
	outfile->name = get_file_name(file_name);
	if (mode)
		outfile->io[WRITE] = \
			open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		outfile->io[WRITE] = \
			open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	outfile->io[READ] = open(file_name, O_RDONLY);
	new_el = ft_lstnew(outfile);
	if (!new_el)
		exit(EXIT_FAILURE);
	ft_lstadd_back(files, new_el);
}

char	*get_file_name(char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name);
	if (file_name[len - 1] == ' ')
		file_name[len - 1] = '\0';
	return (file_name);
}

int	heredoc(const char *end)
{
	pid_t	hd;
	int		heredocfd;
	int		st_exit;

	heredocfd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!heredocfd)
		exit(EXIT_FAILURE);
	signal(SIGINT, SIG_IGN);
	hd = fork();
	if (hd < 0)
		exit(EXIT_FAILURE);
	else if (hd == 0)
		run_heredoc(end, heredocfd);
	waitpid(hd, &st_exit, WUNTRACED);
	ft_signal();
	if (WIFSIGNALED(st_exit) != 0)
	{
		printf("\n");
		return (unlink("heredoc"), -1);
	}
	close(heredocfd);
	return (open("heredoc", O_RDONLY));
}

void	run_heredoc(const char *end, const int hdfile)
{
	char	*input_line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		input_line = readline("> ");
		if (input_line == NULL)
			exit(0);
		if (ft_strncmp(input_line, end, ft_strlen(input_line)) == 0)
			break ;
		ft_putendl_fd(input_line, hdfile);
		free(input_line);
	}
	exit(EXIT_SUCCESS);
}
