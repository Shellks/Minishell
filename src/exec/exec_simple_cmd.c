/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:22:29 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/21 14:06:33 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	cmd_is_builtin(t_data *data, t_exec *exec, t_parser *parse)
{
	if (parse->cmd[0] && is_builtin(data, parse))
	{
		if (exec->flag_in != -1)
			close(exec->infile);
		if (exec->flag_out != -1)
			close(exec->outfile);
		ft_free_exit(data, g_status, NULL);
	}
}

static void	child_without_pipe(t_data *data, t_exec *exec, t_parser *parse)
{
	char	**env_tab;
	char	*cmd;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, ft_ctrl_c_exec);
	close(exec->fd_stdin);
	close(exec->fd_stdout);
	if (exec->flag_out != -1)
	{
		if (dup2(exec->outfile, STDOUT_FILENO) < 0)
			ft_free_exit(data, ERR_EXEC, "Exec error0\n");
		close(exec->outfile);
	}
	cmd_is_builtin(data, exec, parse);
	if (parse->cmd[0])
	{
		cmd = ft_get_cmd(data, parse);
		env_tab = get_env_tab(data, data->env);
		execve(cmd, parse->cmd, env_tab);
	}
	ft_free_exit(data, ERR_EXEC, NULL);
}

static void	exec_cmd_without_pipe(t_data *data, t_exec *exec, t_parser *parse)
{
	exec->pid = fork();
	if (exec->pid == -1)
		ft_free_exit(data, ERR_FORK, "Error with creating fork\n");
	if (exec->pid == 0)
		child_without_pipe(data, exec, parse);
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
	exec_cmd_without_pipe(data, exec, parse);
	waitpid(exec->pid, &g_status, 0);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(exec->fd_stdin, STDIN_FILENO);
	dup2(exec->fd_stdout, STDOUT_FILENO);
	close(exec->fd_stdin);
	close(exec->fd_stdout);
	if (!WIFSIGNALED(g_status))
		g_status = WEXITSTATUS(g_status);
	else if (WIFSIGNALED(g_status))
	{
		if (WTERMSIG(g_status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		g_status = 128 + WTERMSIG(g_status);
	}
}