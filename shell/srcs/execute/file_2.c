/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:39:21 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/19 22:11:12 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_input(t_list **files, t_redirection rd)
{
	t_file	*infile;
	t_list	*new_el;

	if (rd.non)
		return (printf("minishell : %s: ambiguous redirect\n", rd.non), -1);
	infile = (t_file *)malloc(sizeof(t_file));
	if (!infile)
		exit(EXIT_FAILURE);
	if (is_exist((const t_list *)(*files), rd.file))
		return (free(infile), 0);
	infile->name = (char *)rd.file;
	infile->io[WRITE] = NO_FILE;
	infile->io[READ] = open(rd.file, O_RDONLY);
	new_el = ft_lstnew(infile);
	if (!new_el)
		exit(EXIT_FAILURE);
	ft_lstadd_back(files, new_el);
	return (1);
}

void	add_output(t_list **files, const t_redirection rd, const int mode)
{
	t_file	*outfile;
	t_list	*new_el;

	if (rd.non)
	{
		printf("minishell : %s: ambiguous redirect\n", rd.non);
		return ;
	}
	if (replace_redir(files, rd.file, mode))
		return ;
	outfile = (t_file *)malloc(sizeof(t_file));
	if (!outfile)
		exit(EXIT_FAILURE);
	outfile->name = get_file_name(rd.file);
	if (mode)
		outfile->io[WRITE] = \
			open(rd.file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		outfile->io[WRITE] = \
			open(rd.file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	outfile->io[READ] = open(rd.file, O_RDONLY);
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

	heredocfd = open(HD, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
	if (WIFSIGNALED(st_exit))
	{
		printf("\n");
		return (unlink(HD), -1);
	}
	close(heredocfd);
	return (open(HD, O_RDONLY, 0644));
}

void	run_heredoc(const char *end, const int hdfile)
{
	char	*input_line;

	signal(SIGINT, heredoc_signal);
	while (1)
	{
		input_line = readline("> ");
		if (input_line == NULL)
			exit(0);
		if (ft_strncmp(input_line, end, ft_strlen(input_line) + 1) == 0)
			break ;
		ft_putendl_fd(input_line, hdfile);
		free(input_line);
	}
	exit(EXIT_SUCCESS);
}
