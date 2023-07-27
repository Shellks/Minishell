/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:36:51 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/27 14:22:37 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_dup_manager(t_data *data, t_exec *exec)
{
	if (exec->flag_in == 1)
	{
		ft_dup(data, exec->infile, STDIN_FILENO);
	}
	else if (exec->flag_in == 2)
	{
		exec->infile = open(data->here_doc_path->redirec, O_RDONLY);
		if (exec->infile < 0)
			ft_free_exit(data, ERR_OPEN, "Error opening file\n");
		ft_dup(data, exec->infile, STDIN_FILENO);
		unlink(data->here_doc_path->redirec);
	}
}

void	ft_std_manager(t_data *data, int STDIN, int STDOUT)
{
	ft_dup(data, STDIN, STDIN_FILENO);
	ft_dup(data, STDOUT, STDOUT_FILENO);
	if (!WIFSIGNALED(g_status))
		g_status = WEXITSTATUS(g_status);
	else if (WIFSIGNALED(g_status))
	{
		if (WTERMSIG(g_status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		g_status = 128 + WTERMSIG(g_status);
	}
}

void	ft_exit_execve_fail(t_data *data, t_exec *exec, char *cmd, char **tab)
{
	if (cmd)
		free(cmd);
	if (tab)
		ft_free_split(tab);
	ft_close(STDIN_FILENO, STDOUT_FILENO, -1);
	ft_close_all(data, exec, IS_PIPE);
	ft_child_exit(data, exec, IS_NOT_PIPE);
}

void	ft_redir_error(t_redir *redir, t_exec *exec)
{
	struct stat	path;

	if (!redir->redirec[0])
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
	else if (stat(redir->redirec, &path))
	{
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		ft_putstr_fd(redir->redirec, 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->redirec, 2);
		ft_putstr_fd(" permission denied\n", 2);
	}
	g_status = 1;
	exec->exit_status = 1;
}
