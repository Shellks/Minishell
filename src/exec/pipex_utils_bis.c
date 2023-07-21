/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:16:19 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/21 14:22:19 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_std_manager(int STDIN, int STDOUT)
{
	int	wait_all;

	wait_all = 0;
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	while (wait_all != -1)
		wait_all = waitpid(-1, NULL, 0);
	dup2(STDIN, STDIN_FILENO);
	dup2(STDOUT, STDOUT_FILENO);
	close(STDIN);
	close(STDOUT);
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
