/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:39:33 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/16 09:34:44 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	last_process(t_data *data, t_exec *exec, t_parser *parse)
{	
	if (pipe(exec->pipes) == -1)
		ft_free_exit(data, ERR_PIPE, "Error with creating pipe\n");
	exec->pid = fork ();
	if (exec->pid == -1)
		ft_free_exit(data, ERR_FORK, "Error with creating fork\n");
	if (exec->pid == 0)
		last_child(data, exec, parse);
	else
	{
		//ft_close a mettre la
		if (exec->flag_out != -1)
		 	close(exec->outfile);
		close(exec->pipes[0]);
		close(exec->pipes[1]);
	}
}

static void	ft_parent_pattern(t_data *data, t_exec *exec)
{
	if (exec->flag_out != -1)
		 	close(exec->outfile);
		close(exec->pipes[1]);
	if (exec->flag_in == -1)
	{
		if (dup2(exec->pipes[0], STDIN_FILENO) < 0)
		{
			close(exec->pipes[0]);
			ft_free_exit(data, ERR_DUP, "Error with dup\n");
		}
	}
	else
	{
		if (dup2(exec->infile, STDIN_FILENO) < 0)
		{
			close(exec->pipes[0]);
			ft_free_exit(data, ERR_DUP, "Error with dup\n");
		}
		close(exec->infile);
	}
	close(exec->pipes[0]);
}

static void	parent_process(t_data *data, t_exec *exec, t_parser *parse)
{	
	 if (pipe(exec->pipes) == -1)
	 	ft_free_exit(data, ERR_PIPE, "Error with creating pipe\n");
	exec->pid = fork ();
	if (exec->pid == -1)
		ft_free_exit(data, ERR_FORK, "Error with creating fork\n");
	if (exec->pid == 0)
	{
		//dprintf(2,"parse->cmd = %s\n", parse->cmd[0]);
		if (access(parse->cmd[0], R_OK) == 0)
			ft_free_exit(data, ERR_EXEC, "Exec error du acces bizarre\n");
		child_process(data, exec, parse);
	}
	else
		ft_parent_pattern(data, exec);
}
void	pipex(t_data *data, t_exec *exec)
{
	t_parser	*parse;

	exec->fd_stdin = dup(STDIN_FILENO);
	exec->fd_stdout = dup(STDOUT_FILENO);
	parse = data->parser;
	while (parse && parse->next)
	{
		if (ft_set_redir(data, parse, exec) == false)
		{
			parse = parse->next;
			if (!parse->next)
				return ;
		}
		parent_process(data, exec, parse);
		parse = parse->next;
	}
	if (ft_set_redir(data, parse, exec) == false)
	{
		ft_std_manager(exec->fd_stdin, exec->fd_stdout);
		return ;
	}
	last_process(data, exec, parse);
	waitpid(exec->pid, &exec->status, 0);
	ft_std_manager(exec->fd_stdin, exec->fd_stdout);
	close(exec->fd_stdin);
	close(exec->fd_stdout);
}
