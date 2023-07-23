/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:46:49 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/23 17:53:18 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	child_heredoc_expand(t_data *data, t_redir *re, int pipe[2])
{
	char	*str;

	close(pipe[0]);
	while (1)
	{
		str = readline("> ");
		if (!str)
			break ;
		if (ft_strncmp(str, re->redirec, ft_strlen(re->redirec)) == 0)
			break ;
		str = expand_here_doc(data, str);
		ft_putstr_fd(str, pipe[1]);
		ft_putstr_fd("\n", pipe[1]);
		free (str);
	}
	if (str)
		free(str);
	close(pipe[1]);
}

static void	child_heredoc(t_redir *re, int pipe[2])
{
	char	*str;

	close(pipe[0]);
	while (1)
	{
		str = readline("> ");
		if (!str)
			break ;
		if (ft_strncmp(str, re->redirec, ft_strlen(re->redirec)) == 0)
			break ;
		free (str);
	}
	if (str)
		free(str);
	close(pipe[1]);
}

static void	parent_heredoc(t_redir *re, int pipe_connect[2], int fd)
{
	char	*str;

	close(pipe_connect[1]);
	while (1)
	{
		str = get_next_line(pipe_connect[0]);
		if (!str)
			break ;
		if (ft_strncmp(str, re->redirec, ft_strlen(re->redirec)) == 0)
			break ;
		ft_putstr_fd(str, fd);
		free(str);
	}
	if (str)
		free(str);
	close(fd);
	close(pipe_connect[0]);
}

void	get_heredoc(t_data *data, t_redir *redir, t_exec *exec)
{
	int	pipe_connect[2];
	int	fd;

	signal(SIGINT, SIG_IGN);
	dup2(exec->fd_stdin, STDIN_FILENO);
	dup2(exec->fd_stdout, STDOUT_FILENO);
	if (exec->flag_in == 1)
	{
		exec->flag_in = -1;
		close(exec->infile);
	}
	if (pipe(pipe_connect) < 0)
		ft_free_exit(data, ERR_FORK, "minishell: error with creating pipe\n");
	exec->pid = fork();
	if (exec->pid == -1)
		ft_free_exit(data, ERR_FORK, "Error with creating fork\n");
	if (exec->pid == 0)
	{
		signal(SIGINT, ft_ctrl_c_heredoc);
		if (redir->quote != NONE)
			child_heredoc(redir, pipe_connect);
		else
			child_heredoc_expand(data, redir, pipe_connect);
		ft_close(exec->fd_stdin, exec->fd_stdout, -1);
		ft_free_exit(data, 0, NULL);
	}
	get_here_doc_fd(data, redir, &fd);
	parent_heredoc(redir, pipe_connect, fd);
	waitpid(exec->pid, &g_status, 0);
	exec->flag_in = 2;
}
