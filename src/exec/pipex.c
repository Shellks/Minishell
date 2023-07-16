/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:39:33 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/15 14:02:58 by nibernar         ###   ########.fr       */
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
			ft_free_exit(data, ERR_EXEC, "Exec error\n");
		child_process(data, exec, parse);
	}
	else
	{
		close(exec->pipes[1]);
		if (dup2(exec->pipes[0], 0) < 0)
		{
			close(exec->pipes[0]);
			// ft_close(p, 1, 0, 1);
			// ft_free_parent(p, ERR_DUP);
		}
		close(exec->pipes[0]);
	}
}
void	pipex(t_data *data, t_exec *exec)
{
	int			STDOUT_CPY;
	int			STDIN_CPY;
	t_parser	*parse;
	int	wait_all;

	STDOUT_CPY = dup(STDOUT_FILENO);
	STDIN_CPY = dup(STDIN_FILENO);
	parse = data->parser;
	wait_all = 0;
	if (exec->flag_in == 1)
	{
		dup2(exec->infile, 0);
	}
	else if (exec->flag_in == 2)
	{
		dup2(exec->here_doc[0], 0);
		close(exec->here_doc[1]);
	}
	while (parse && parse->next)
	{
		parent_process(data, exec, parse);
		parse = parse->next;
	}
	last_process(data, exec, parse);
	waitpid(exec->pid, &exec->status, 0);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	while (wait_all != -1)
		wait_all = waitpid(-1, NULL, 0);
	dup2(STDIN_CPY, STDIN_FILENO);
	dup2(STDOUT_CPY, STDOUT_FILENO);
}
