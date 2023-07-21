/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:46:49 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/21 13:35:01 by nibernar         ###   ########.fr       */
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

static void	child_heredoc(t_redir *re, int pipe_connect[2])
{
	char	*str;

	close(pipe_connect[0]);
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
	close(pipe_connect[1]);
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

void	get_child_hered(t_data *data, t_redir *redir, t_exec *exec, int *pipe)
{
	if (exec->pid == 0)
	{
		signal(SIGINT, ft_ctrl_c_heredoc);
		if (redir->quote != NONE)
			child_heredoc(redir, pipe);
		else
			child_heredoc_expand(data, redir, pipe);
		close(exec->fd_stdin);
		close(exec->fd_stdout);
		ft_free_exit(data, 0, NULL);
	}
}

void	get_heredoc(t_data *data, t_redir *redir, t_exec *exec)
{
	int	pipe_connect[2];
	int	fd;

	signal(SIGINT, SIG_IGN);
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
	get_child_hered(data, redir, exec, pipe_connect);
	get_here_doc_fd(data, redir, &fd);
	parent_heredoc(redir, pipe_connect, fd);
	waitpid(exec->pid, &g_status, 0);
	exec->flag_in = 2;
}