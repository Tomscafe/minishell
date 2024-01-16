/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:02:45 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/16 21:29:55 by juhyelee         ###   ########.fr       */
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
	char	*infile;
	char	*outfile;
	int		is_append;
	int		is_heredoc;

	infile = get_infile(rd, &is_heredoc);
	outfile = get_outfile(rd, &is_append);
	if (infile && is_heredoc)
		open_heredoc(&(exe->files), infile);
	else if (infile)
		open_exist_file(&(exe->files), infile);
	if (outfile)
		create_new_file(&(exe->files), outfile, is_append);
}

void	open_heredoc(t_list **list, const char *file_name)
{
	t_file	*file;
	t_list	*new_el;

	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		exit(EXIT_FAILURE);
	file->is_heredoc = 1;
	file->name = (char *)file_name;
	file->io[WRITE] = 0;
	file->io[READ] = heredoc(file_name);
	new_el = ft_lstnew(file);
	if (!new_el)
		exit(EXIT_FAILURE);
	ft_lstadd_back(list, new_el);
}

void	open_exist_file(t_list **list, const char *file_name)
{
	t_file	*file;
	t_list	*new_el;

	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		exit(EXIT_FAILURE);
		file->is_heredoc = 0;
	file->name = (char *)file_name;
	file->io[WRITE] = 0;
	file->io[READ] = open(file_name, O_RDONLY);
	if (file->io[READ] < 0)
	{
		free(file);
		return ;
	}
	new_el = ft_lstnew(file);
	if (!new_el)
		exit(EXIT_FAILURE);
	ft_lstadd_back(list, new_el);
}

void	create_new_file(t_list **list, const char *file_name, const int mode)
{
	t_file	*file;
	t_list	*new_el;

	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		exit(EXIT_FAILURE);
	file->is_heredoc = 0;
	file->name = (char *)file_name;
	if (mode)
		file->io[WRITE] = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		file->io[WRITE] = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	file->io[READ] = open(file_name, O_RDONLY);
	new_el = ft_lstnew(file);
	if (!new_el)
		exit(EXIT_FAILURE);
	ft_lstadd_back(list, new_el);
}
