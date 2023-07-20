/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:22:29 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/20 10:16:45 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	child_process1(t_data *data, t_exec *exec, t_parser *parse)
{
	char	**env_tab;
	char	*cmd;

	if (exec->flag_out != -1)
	{
	  	if (dup2(exec->outfile, STDOUT_FILENO) < 0)
	   		ft_free_exit(data, ERR_EXEC, "Exec error0\n");
		close(exec->outfile);
	}
	if (parse->cmd[0] && is_builtin(data, parse))
	{
		if (exec->flag_in != -1)
			close(exec->infile);
		if (exec->flag_out != -1)
			close(exec->outfile);
		close(exec->fd_stdin);
		close(exec->fd_stdout);
		ft_free_exit(data, g_status, NULL);
	}
	if (parse->cmd[0])
	{
			cmd = ft_get_cmd(data, parse);
			env_tab = get_env_tab(data,data->env);
			execve(cmd, parse->cmd, env_tab);
	}
	close(exec->fd_stdin);
	close(exec->fd_stdout);
	ft_free_exit(data, ERR_EXEC, "Error with executing execve");
}

static void	exec_simple_cmd1(t_data *data, t_exec *exec, t_parser *parse)
{	
	// if (pipe(exec->pipes) == -1)
	//  	ft_free_exit(data, ERR_EXEC, "Exec prout error\n");
	exec->pid = fork ();
	// if (exec->pid == -1)
	// 	ft_close_free(p, CLOSE_ALL, FREE_PARENT, ERR_FORK);
	if (exec->pid == 0)
		child_process1(data, exec, parse);
	else
	{
		if (exec->flag_in == 2)
		{
			
		}
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
	t_parser	*parse;

	exec->fd_stdin = dup(STDOUT_FILENO);
	exec->fd_stdout = dup(STDIN_FILENO);
	parse = data->parser;
	if (data->parser->cmd[0])
		ft_dup_manager(data, exec);
	exec_simple_cmd1(data, exec, parse);
	waitpid(exec->pid, &exec->status, 0);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(exec->fd_stdin, STDIN_FILENO);
	dup2(exec->fd_stdout, STDOUT_FILENO);
	close(exec->fd_stdin);
	close(exec->fd_stdout);
}
