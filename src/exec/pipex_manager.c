/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:36:51 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/27 01:03:13 by acarlott         ###   ########lyon.fr   */
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
	int	wait_all;

	wait_all = 1;
	printf("Test\n");
	//ft_close(STDIN_FILENO, STDOUT_FILENO, -1);
	while (wait_all != -1)
		wait_all = waitpid(-1, NULL, 0);
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
