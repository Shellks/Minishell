/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:29:26 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/28 12:29:44 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_close(int fd1, int fd2, int fd3)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	if (fd3 != -1)
		close(fd3);
}

void	ft_close_all(t_data *data, t_exec *exec, int sign)
{
	if (exec->flag_in == 1)
	{
		exec->flag_in = -1;
		close(exec->infile);
	}
	else if (exec->flag_in == 2)
	{
		exec->flag_in = -1;
		close(exec->infile);
		unlink(data->here_doc_path->redirec);
	}
	if (exec->flag_out == 1)
	{
		exec->flag_out = -1;
		close(exec->outfile);
	}
	if (sign == IS_PIPE)
	{
		if (exec->pipes[0] != -1)
			close(exec->pipes[0]);
		if (exec->pipes[1] != -1)
			close(exec->pipes[1]);
	}
}
