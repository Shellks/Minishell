/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:22:29 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/16 11:34:52 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_cmd1(char **path, char *cmd)
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
		if (access(cmd2, X_OK) == 0)
			return (cmd2);
		free (cmd2);
		i++;
	}
	return (NULL);
}

static void	child_process1(t_data *data, t_exec *exec, t_parser *parse)
{
	char	*cmd2;

	(void)exec;
	close(0);
	if (dup2(1, 1) < 0)
		ft_free_exit(data, ERR_EXEC, "Exec error1\n");
	cmd2 = get_cmd1(data->path, parse->cmd[0]);
	if (cmd2 == NULL)
	{
		ft_putstr_fd("Command not found2: ", 2);
		ft_putstr_fd(parse->cmd[0], 2);
		ft_putstr_fd("\n", 2);
		close(1);
		//ft_close_free(p, CLOSE_FILE, FREE_CHILD, ERR_CMD);
	}
	execve(cmd2, parse->cmd, data->path);
	close(1);
	// ft_close_free(p, CLOSE_FILE, FREE_CHILD, ERR_EXEC);
}

static void	exec_simple_cmd1(t_data *data, t_exec *exec, t_parser *parse)
{	
	// if (pipe(exec->pipes) == -1)
	//  	ft_free_exit(data, ERR_EXEC, "Exec prout error\n");
	exec->pid = fork ();
	// if (exec->pid == -1)
	// 	ft_close_free(p, CLOSE_ALL, FREE_PARENT, ERR_FORK);
	if (exec->pid == 0)
	{
		if (access(parse->cmd[0], R_OK) == 0)
			ft_free_exit(data, ERR_EXEC, "Exec error\n");
		child_process1(data, exec, parse);
	}
	else
	{
		close(1);
		if (dup2(0, 0) < 0)
		{
			close(0);
			// ft_close(p, 1, 0, 1);
			// ft_free_parent(p, ERR_DUP);
		}
		close(0);
	}
}

void	exec_simple_cmd(t_data *data, t_exec *exec)
{
	int			STDOUT_CPY;
	int			STDIN_CPY;
	t_parser	*parse;

	STDOUT_CPY = dup(STDOUT_FILENO);
	STDIN_CPY = dup(STDIN_FILENO);
	parse = data->parser;
	if (exec->flag_in == 1)
	{
		dup2(exec->infile, 0);
	}
	else if (exec->flag_in == 2)
	{
		dup2(exec->here_doc[0], 0);
		close(exec->here_doc[1]);
	}
	exec_simple_cmd1(data, exec, parse);
	waitpid(exec->pid, &exec->status, 0);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(STDIN_CPY, STDIN_FILENO);
	dup2(STDOUT_CPY, STDOUT_FILENO);
}