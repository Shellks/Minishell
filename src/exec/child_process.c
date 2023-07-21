/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:39:17 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/21 12:45:01 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(t_data *data, t_parser *parse)
{
	int	len;

	len = 0;
	if (!ft_strncmp(parse->cmd[0], "pwd", 3) && ++len)
		printf("%s\n", data->pwd->content);
	else if (!ft_strncmp(parse->cmd[0], "unset", 5) && ++len)
		g_status = ft_unset(data, parse);
	else if (!ft_strncmp(parse->cmd[0], "export", 6) && ++len)
		g_status = ft_export(data, parse);
	else if (!ft_strncmp(parse->cmd[0], "exit", 4) && ++len)
		ft_exit(data);
	else if (!ft_strncmp(parse->cmd[0], "env", 3) && ++len)
		g_status = ft_env(data);
	else if (!ft_strncmp(parse->cmd[0], "echo", 4) && ++len)
		g_status = ft_echo(parse);
	else if (!ft_strncmp(parse->cmd[0], "cd", 2) && ++len)
		g_status = ft_cd(data, parse->cmd);
	return (len);
}

void	last_child(t_data *data, t_exec *exec, t_parser *parse)
{
	char	**env_tab;
	char	*cmd;

	signal(SIGINT, ft_ctrl_c_exec);
	signal(SIGQUIT, SIG_DFL);
	close(exec->fd_stdin);
	close(exec->fd_stdout);
	close(exec->pipes[0]);
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
		close(exec->pipes[1]);
		ft_free_exit(data, g_status, NULL);
	}
	if (parse->cmd[0])
	{
			cmd = ft_get_cmd(data, parse);
			env_tab = get_env_tab(data);
			execve(cmd, parse->cmd, env_tab);
	}
	close(exec->pipes[1]);
	g_status = 0;
	ft_free_exit(data, g_status, NULL);
}

void	child_process(t_data *data, t_exec *exec, t_parser *parse)
{
	char	**env_tab;
	char	*cmd;

	signal(SIGINT, ft_ctrl_c_exec);
	signal(SIGQUIT, SIG_DFL);
	close(exec->pipes[0]);
	close(exec->fd_stdin);
	close(exec->fd_stdout);
	if (exec->flag_out != -1)
	{
		if (dup2(exec->outfile, STDOUT_FILENO) < 0)
			ft_free_exit(data, ERR_DUP, "Error with creating dup\n");
		close(exec->outfile);
	}
	else
	{
		if (dup2(exec->pipes[1], STDOUT_FILENO) < 0)
			ft_free_exit(data, ERR_DUP, "Error with creating dup\n");
		close(exec->pipes[1]);
	}
	if (parse->cmd[0] && is_builtin(data, parse))
	{
		if (exec->flag_in != -1)
			close(exec->infile);
		if (exec->flag_out != -1)
			close(exec->outfile);
		close(exec->pipes[1]);
		ft_free_exit(data, g_status, NULL);
	}
	if (parse->cmd[0])
	{
		cmd = ft_get_cmd(data, parse);
		env_tab = get_env_tab(data);
		execve(cmd, parse->cmd, env_tab);
	}
	close(exec->pipes[1]);
	g_status = 0;
	ft_free_exit(data, g_status, NULL);
}
