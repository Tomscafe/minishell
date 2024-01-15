/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:39:21 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/15 22:57:26 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (WIFEXITED(st_exit) != 0)
		unlink("heredoc");
	close(heredocfd);
	return (open("heredoc", O_RDONLY));
}

void	run_heredoc(const char *end, const int hdfile)
{
	char	*input_line;
	struct	termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
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