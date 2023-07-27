/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:39:33 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/27 13:10:55 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(t_data *data, t_parser *parse)
{
	int	len;

	len = 0;
	if (!ft_strncmp(parse->cmd[0], "pwd", 3) && \
	(int)ft_strlen(parse->cmd[0]) == 3 && ++len)
		ft_pwd(data);
	else if (!ft_strncmp(parse->cmd[0], "unset", 5) && \
	(int)ft_strlen(parse->cmd[0]) == 5 && ++len)
		ft_unset(data, parse);
	else if (!ft_strncmp(parse->cmd[0], "export", 6) && \
	(int)ft_strlen(parse->cmd[0]) == 6 && ++len)
		ft_export(data, parse);
	else if (!ft_strncmp(parse->cmd[0], "exit", 4) && \
	(int)ft_strlen(parse->cmd[0]) == 4 && ++len)
		ft_exit(data, parse);
	else if (!ft_strncmp(parse->cmd[0], "env", 3) && \
	(int)ft_strlen(parse->cmd[0]) == 3 && ++len)
		g_status = ft_env(data);
	else if (!ft_strncmp(parse->cmd[0], "echo", 4) && \
	(int)ft_strlen(parse->cmd[0]) == 4 && ++len)
		g_status = ft_echo(parse);
	else if (!ft_strncmp(parse->cmd[0], "cd", 2) && \
	(int)ft_strlen(parse->cmd[0]) == 2 && ++len)
		g_status = ft_cd(data, parse->cmd);
	return (len);
}

static void	child_process_manager(t_data *data, t_exec *exec, t_parser *parse)
{
	ft_close(exec->fd_stdin, exec->fd_stdout, -1);
	if (exec->flag_out != -1 && exec->flag_out != -2)
		dup2(exec->outfile, STDOUT_FILENO);
	else if (parse->next) 
		dup2(exec->pipes[1], STDOUT_FILENO);
	if (exec->flag_in == -2 || exec->flag_out == -2)
		return (g_status = 1, ft_child_exit(data, exec, IS_PIPE));
}

void	child_process(t_data *data, t_exec *exec, t_parser *parse)
{
	char	**env_tab;
	char	*cmd;

	signal(SIGINT, ft_ctrl_c_exec);
	signal(SIGQUIT, SIG_DFL);
	cmd = NULL;
	env_tab = NULL;
	child_process_manager(data, exec, parse);
	if (parse->cmd[0] && is_builtin(data, parse))
		ft_child_exit(data, exec, IS_PIPE);
	else if (parse->cmd[0])
	{
		cmd = ft_get_cmd(data, parse, exec);
		env_tab = get_env_tab(data);
		ft_close(exec->pipes[0], exec->pipes[1], -1);
		execve(cmd, parse->cmd, env_tab);
	}
	ft_exit_execve_fail(data, exec, cmd, env_tab);
}

static void	parent_process(t_data *data, t_exec *exec, t_parser *parse)
{
	if (pipe(exec->pipes) == -1)
		ft_free_exit(data, ERR_PIPE, "Error with creating pipe\n");
	exec->pid = fork ();
	if (exec->pid == -1)
		ft_free_exit(data, ERR_FORK, "Error with creating fork\n");
	if (exec->pid == 0)
		child_process(data, exec, parse);
	else
	{
		if (exec->flag_out > 0)
			close(exec->outfile);
		if (parse->next && (exec->flag_in == -1 || exec->flag_in == -2))
			ft_dup(data, exec->pipes[0], STDIN_FILENO);
		else if (parse->next)
		{
			ft_dup(data, exec->infile, STDIN_FILENO);
			close(exec->pipes[0]);
		}
		close(exec->pipes[1]);
	}
}

void	pipex(t_data *data, t_exec *exec)
{
	int			error;
	t_parser	*parse;

	signal(SIGINT, SIG_IGN);
	parse = data->parser;
	exec->fd_stdin = dup(STDIN_FILENO);
	exec->fd_stdout = dup(STDOUT_FILENO);
	while (parse)
	{
		ft_set_redir(data, parse, exec);
		ft_dup_manager(data, exec);
		parent_process(data, exec, parse);
		parse = parse->next;
	}
	waitpid(exec->pid, &g_status, 0);
	ft_close(STDIN_FILENO, STDOUT_FILENO, -1);
	while (waitpid(-1, &error, 0) > 0)
		;
	ft_std_manager(data, exec->fd_stdin, exec->fd_stdout);
	ft_close_all(data, exec, IS_PIPE);
}
