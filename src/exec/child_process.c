/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:39:17 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/15 20:20:33 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_cmd(char **path, char *cmd)
{
	char	*temp;
	char	*cmd2;
	int		i;

	i = 0;
	if (access(cmd, 0) == 0)
		return (cmd);
	if (cmd[0] == '/')
		return (NULL);
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		cmd2 = ft_strjoin(temp, cmd);
		free (temp);
		//dprintf(2, "cmd2 = %s\n", cmd2);
		if (access(cmd2, X_OK) == 0)
			return (cmd2);
		free (cmd2);
		i++;
	}
	return (NULL);
}

void	last_child(t_data *data, t_exec *exec, t_parser *parse)
{
	char	*cmd2;

	close(exec->pipes[0]);
	if (exec->flag_out != -1)
	{
	  	if (dup2(exec->outfile, STDOUT_FILENO) < 0)
	   		ft_free_exit(data, ERR_EXEC, "Exec error0\n");
		close(exec->outfile);
	}
	cmd2 = get_cmd(data->path, parse->cmd[0]);
	if (cmd2 == NULL)
	{
		ft_putstr_fd("Command not found1: ", 2);
		ft_putstr_fd(parse->cmd[0], 2);
		ft_putstr_fd("\n", 2);
		close(exec->pipes[1]);
		//ft_close_free(p, CLOSE_FILE, FREE_CHILD, ERR_CMD);
	}
	execve(cmd2, parse->cmd, data->path);
	close(exec->pipes[1]);
	//ft_close_free(p, CLOSE_FILE, FREE_CHILD, ERR_EXEC);
}

void	child_process(t_data *data, t_exec *exec, t_parser *parse)
{
	char	*cmd2;

	
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
	cmd2 = get_cmd(data->path, parse->cmd[0]);
	if (cmd2 == NULL)
	{
		ft_putstr_fd("Command not found2: ", 2);
		ft_putstr_fd(parse->cmd[0], 2);
		ft_putstr_fd("\n", 2);
		close(exec->pipes[1]);
		//ft_close_free(p, CLOSE_FILE, FREE_CHILD, ERR_CMD);
	}
	execve(cmd2, parse->cmd, data->path);
	close(exec->pipes[1]);
	// ft_close_free(p, CLOSE_FILE, FREE_CHILD, ERR_EXEC);
}
