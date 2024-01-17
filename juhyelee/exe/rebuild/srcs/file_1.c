/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:02:45 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/17 17:57:00 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_all_files(t_exe *exe)
{
	int				ret;
	const t_pipe	*p = exe->cmds;

	ret = 1;
	exe->files = NULL;
	ret = open_files(exe, p->first->redirection);
	while (p->next)
	{
		p = p->next;
		ret = open_files(exe, p->first->redirection);
	}
	if (p->second)
		ret = open_files(exe, p->second->redirection);
	return (ret);
}

int	open_files(t_exe *exe, const t_redirection *rd)
{
	int	ret;

	ret = 1;
	while (rd)
	{
		if (ft_strncmp(rd->symbol, ">>", 2) == 0)
			add_output((t_list **)&(exe->files), rd->file, 1);
		else if (rd->symbol[0] == '>')
			add_output((t_list **)&(exe->files), rd->file, 0);
		if (ft_strncmp(rd->symbol, "<<", 2) == 0)
			ret = add_heredoc((t_list **)&(exe->files), rd->file);
		else if (rd->symbol[0] == '<')
			add_input((t_list **)&(exe->files), rd->file);
		rd = rd->next;
	}
	return (ret);
}

int	add_heredoc(t_list **files, const char *end)
{
	t_file	*hd;
	t_list	*new_el;

	hd = (t_file *)malloc(sizeof(t_file));
	if (!hd)
		exit(EXIT_FAILURE);
	hd->name = (char *)end;
	hd->io[WRITE] = 0;
	hd->io[READ] = heredoc(end);
	if (hd->io[READ] == HD_SIG)
		return (0);
	new_el = ft_lstnew(hd);
	if (!new_el)
		exit(EXIT_FAILURE);
	ft_lstadd_back(files, new_el);
	return (1);
}

int	is_exist(const t_list *files, const char *file_name)
{
	t_file	*content;

	while (files)
	{
		content = files->content;
		if (ft_strncmp(content->name, file_name, \
					ft_strlen(content->name) + 1) == 0)
			return (1);
		files = files->next;
	}
	return (0);
}

void	clear_file(void *to_del)
{
	t_file	*file;

	file = to_del;
	if (file->io[READ] > 1)
		close(file->io[READ]);
	if (file->io[WRITE] > 1)
		close(file->io[WRITE]);
	free(file);
}
