/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:55:59 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/24 23:47:37 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	get_infile(t_data *data, t_redir *redir, t_exec *exec)
{
	if (!redir->redirec)
		return (false);
	if (exec->flag_in == 1)
	{
		exec->flag_in = -1;
		close(exec->infile);
	}
	else if (exec->flag_in == 2)
	{
		exec->flag_in = 0;
		unlink(data->here_doc_path->redirec);
	}
	exec->infile = open(redir->redirec, O_RDONLY);
	if (exec->infile < 0)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(redir->redirec, 2);
		ft_putstr_fd("\n", 2);
		exec->flag_in = -2;
		return (false);
	}
	exec->flag_in = 1;
	return (true);
}

static bool	get_outfile(t_redir *redir, t_exec *exec)
{
	if (!redir->redirec)
		return (false);
	if (exec->flag_out == 1)
	{
		exec->flag_out = -1;
		close(exec->outfile);
	}
	exec->outfile = open(redir->redirec, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (exec->outfile < 0)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(redir->redirec, 2);
		ft_putstr_fd("\n", 2);
		exec->flag_out = -2;
		return (false);
	}
	exec->flag_out = 1;
	return (true);
}

static bool	get_append(t_redir *redir, t_exec *exec)
{
	if (!redir->redirec)
		return (false);
	if (exec->flag_out == 1)
	{
		exec->flag_out = -1;
		close(exec->outfile);
	}
	exec->outfile = open(redir->redirec, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (exec->outfile < 0)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(redir->redirec, 2);
		ft_putstr_fd("\n", 2);
		return (false);
	}
	exec->flag_out = 1;
	return (true);
}

static bool	redir_loop(t_data *data, t_exec *exec, t_redir *redir)
{
	if (redir->token == HERE_DOC)
		get_heredoc(data, redir, exec);
	if (redir->token == INFILE)
	{
		if (get_infile(data, redir, exec) == false)
			return (false);
	}
	else if (redir->token == OUTFILE)
	{
		if (get_outfile(redir, exec) == false)
			return (false);
	}
	else if (redir->token == OUTFILE_APPEND)
	{
		if (get_append(redir, exec) == false)
			return (false);
	}
	return (true);
}

bool	ft_set_redir(t_data *data, t_parser *parser, t_exec *exec)
{
	t_redir	*tmp_redir;

	exec->flag_in = -1;
	exec->flag_out = -1;
	if (!parser->redir)
		return (true);
	tmp_redir = parser->redir;
	while (tmp_redir)
	{
		if (redir_loop(data, exec, tmp_redir) == false)
		{
			if (exec->flag_in == 1)
				close(exec->infile);
			if (exec->flag_out == 1)
				close(exec->outfile);
			return (false);
		}
		tmp_redir = tmp_redir->next;
	}
	return (true);
}
