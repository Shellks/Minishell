/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:04:16 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/19 15:12:14 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_ctrl_c_heredoc(int signum)
{
	if (signum == 2)
		ft_free_exit(ft_get_data(NULL), 130, NULL);
}

void	ft_ctrl_c_exec(int signum)
{
	(void)signum;
}

void	ft_ctrl_c(int signum)
{
	(void)signum;
	g_status = 130;
	rl_on_new_line();
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
}
