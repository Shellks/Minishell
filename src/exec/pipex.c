/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:39:33 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/15 16:26:14 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	last_process(t_data *data, t_exec *exec, t_parser *parse)
{	
	if (pipe(exec->pipes) == -1)
		ft_free_exit(data, ERR_PIPE, "Exec error\n");
	exec->pid = fork ();
	// if (exec->pid == -1)
	// 	ft_close_free(p, CLOSE_ALL, FREE_PARENT, ERR_FORK);
	if (exec->pid == 0)
		last_child(data, exec, parse);
	else
	{
		close(exec->pipes[0]);
		close(exec->pipes[1]);
	}
}

static void	parent_process(t_data *data, t_exec *exec, t_parser *parse)
{	
	 if (pipe(exec->pipes) == -1)
	 	ft_free_exit(data, ERR_EXEC, "Exec prout error\n");
	exec->pid = fork ();
	// if (exec->pid == -1)
	// 	ft_close_free(p, CLOSE_ALL, FREE_PARENT, ERR_FORK);
	if (exec->pid == 0)
	{
		//dprintf(2,"parse->cmd = %s\n", parse->cmd[0]);
		if (access(parse->cmd[0], R_OK) == 0)
			ft_free_exit(data, ERR_EXEC, "Exec error du acces bizarre\n");
		child_process(data, exec, parse);
	}
	else
	{
		close(exec->pipes[1]);
		if (exec->flag_in == 0)
		{
			if (dup2(exec->pipes[0], STDIN_FILENO) < 0)
			{
				close(exec->pipes[0]);
				// ft_close(p, 1, 0, 1);
				// ft_free_parent(p, ERR_DUP);
			}
		}
		else
		{
			if (dup2(exec->infile, STDIN_FILENO) < 0)
			{
				close(exec->pipes[0]);
				// ft_close(p, 1, 0, 1);
				// ft_free_parent(p, ERR_DUP);
			}
		}
		close(exec->pipes[0]);
	}
}
void	pipex(t_data *data, t_exec *exec)
{
	t_parser	*parse;
	int			STDIN_CPY;
	int			STDOUT_CPY;

	STDIN_CPY = dup(STDIN_FILENO);
	STDOUT_CPY = dup(STDOUT_FILENO);
	parse = data->parser;
	while (parse && parse->next)
	{
		if (ft_set_redir(data, parse, exec) == false)
		{
			parse = parse->next;
			if (parse->next)
				break ;
		}
		parent_process(data, exec, parse);
		parse = parse->next;
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		dup2(STDIN_CPY, STDIN_FILENO);
		dup2(STDOUT_CPY, STDOUT_FILENO);
	}
	if (ft_set_redir(data, parse, exec) == false)
	{
		ft_std_manager(STDIN_CPY, STDOUT_CPY);
		return ;
	}
	last_process(data, exec, parse);
	waitpid(exec->pid, &exec->status, 0);
	ft_std_manager(STDIN_CPY, STDOUT_CPY);
}
