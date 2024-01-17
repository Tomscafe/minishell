/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:02:45 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/17 16:24:46 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_all_files(t_exe *exe)
{
	const t_pipe	*p = exe->cmds;

	exe->files = NULL;
	open_files(exe, p->first->redirection);
	while (p->next)
	{
		p = p->next;
		open_files(exe, p->first->redirection);
	}
	if (p->second)
		open_files(exe, p->second->redirection);
}

void	open_files(t_exe *exe, const t_redirection *rd)
{
	while (rd)
	{
		if (ft_strncmp(rd->symbol, ">>", 2) == 0)
			add_output((t_list **)&(exe->files), rd->file, 1);
		else if (rd->symbol[0] == '>')
			add_output((t_list **)&(exe->files), rd->file, 0);
		if (ft_strncmp(rd->symbol, "<<", 2) == 0)
			add_heredoc((t_list **)&(exe->files), rd->file);
		else if (rd->symbol[0] == '<')
			add_input((t_list **)&(exe->files), rd->file);
		rd = rd->next;
	}
}

void	add_heredoc(t_list **files, const char *end)
{
	t_file	*hd;
	t_list	*new_el;

	hd = (t_file *)malloc(sizeof(t_file));
	if (!hd)
		exit(EXIT_FAILURE);
	hd->is_heredoc = 1;
	hd->is_signal = 0;
	hd->name = (char *)end;
	hd->io[WRITE] = 0;
	hd->io[READ] = heredoc(end);
	if (hd->io[READ] == HD_SIG)
		hd->is_signal = 1;
	new_el = ft_lstnew(hd);
	if (!new_el)
		exit(EXIT_FAILURE);
	ft_lstadd_back(files, new_el);
}

void	add_input(t_list **files, const char *file_name)
{
	t_file	*infile;
	t_list	*new_el;

	infile = (t_file *)malloc(sizeof(t_file));
	if (!infile)
		exit(EXIT_FAILURE);
	infile->is_heredoc = 0;
	infile->is_signal = 0;
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
	outfile->is_heredoc = 0;
	outfile->is_signal = 0;
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
