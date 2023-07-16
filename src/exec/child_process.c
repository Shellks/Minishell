/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:39:17 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/16 09:33:11 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	last_child(t_data *data, t_exec *exec, t_parser *parse)
{
	char	*cmd;

	close(exec->pipes[0]);
	if (exec->flag_out != -1)
	{
	  	if (dup2(exec->outfile, STDOUT_FILENO) < 0)
	   		ft_free_exit(data, ERR_EXEC, "Exec error0\n");
		close(exec->outfile);
	}
	if (parse->cmd)
	{
		cmd = ft_get_cmd(data, parse);
		execve(cmd, parse->cmd, data->path);
	}
	close(exec->pipes[1]);
	//ft_close_free(p, CLOSE_FILE, FREE_CHILD, ERR_EXEC);
}

void	child_process(t_data *data, t_exec *exec, t_parser *parse)
{
	char	*cmd;

	
	close(exec->pipes[0]);
	if (exec->flag_out != -1)
	{
	  	if (dup2(exec->outfile, STDOUT_FILENO) < 0)
	   		ft_free_exit(data, ERR_EXEC, "Exec error0\n");
		//close(exec->outfile);
	}
	else
	{
		if (dup2(exec->pipes[1], STDOUT_FILENO) < 0)
			ft_free_exit(data, ERR_EXEC, "Exec error1\n");
		//close(exec->pipes[1]);
	}
	if (parse->cmd)
	{
		cmd = ft_get_cmd(data, parse);
		execve(cmd, parse->cmd, data->path);
	}
	close(exec->pipes[1]);
	// ft_close_free(p, CLOSE_FILE, FREE_CHILD, ERR_EXEC);
}
