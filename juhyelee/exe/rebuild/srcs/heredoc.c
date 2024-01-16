/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:39:21 by juhyelee          #+#    #+#             */
/*   Updated: 2024/01/16 19:58:51 by juhyelee         ###   ########.fr       */
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
	char			*input_line;
	struct termios	term;

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
		if (ft_strncmp(input_line, end, ft_strlen(end)) == 0)
			break ;
		ft_putendl_fd(input_line, hdfile);
		free(input_line);
	}
	exit(EXIT_SUCCESS);
}

void	close_input(t_table table)
{
	if (table.input != STDIN_FILENO && \
		table.input != STDOUT_FILENO)
		close(table.input);
}

void	close_output(t_table table)
{
	if (table.output != STDOUT_FILENO && \
		table.output != STDIN_FILENO)
		close(table.output);
}

int	execute_exit(const char *arg)
{
	int		exit_num;

	arg += 5;
	if (arg[0] == '\0')
		exit(0);
	exit_num = ft_atoi(arg) % 256;
	exit(exit_num);
}
