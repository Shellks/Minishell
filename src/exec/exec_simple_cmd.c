/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:22:29 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/23 19:00:45 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	child_process1(t_data *data, t_exec *exec, t_parser *parse)
{
	char	**env_tab;
	char	*cmd;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, ft_ctrl_c_exec);
	ft_close(exec->fd_stdin, exec->fd_stdout, -1);
	if (exec->flag_out != -1)
		ft_dup(data, exec->outfile, STDOUT_FILENO);
	if (parse->cmd[0] && is_builtin(data, parse))
	{
		ft_close_all(data, exec, IS_NOT_PIPE);
		ft_free_exit(data, g_status, NULL);
	}
	if (parse->cmd[0])
	{
			cmd = ft_get_cmd(data, parse);
			env_tab = get_env_tab(data);
			execve(cmd, parse->cmd, env_tab);
	}
	ft_close_all(data, exec, IS_NOT_PIPE);
	ft_free_exit(data, ERR_EXEC, NULL);
}

static void	exec_simple_cmd1(t_data *data, t_exec *exec, t_parser *parse)
{
	exec->pid = fork ();
	if (exec->pid == -1)
		ft_free_exit(data, ERR_FORK, "Error with creating fork\n");
	if (exec->pid == 0)
		child_process1(data, exec, parse);
	else
	{
		close(1);
		if (dup2(0, 0) < 0)
			close(0);
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
	waitpid(exec->pid, &g_status, 0);
	ft_std_manager(data, exec->fd_stdin, exec->fd_stdout);
	ft_close_all(data, exec, IS_NOT_PIPE);
}
