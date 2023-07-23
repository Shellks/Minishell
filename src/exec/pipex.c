/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:39:33 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/23 12:25:54 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_std_manager(t_data *data, t_exec *exec, int STDIN, int STDOUT)
{
	int	wait_all;

	(void)data;
	(void)exec;
	wait_all = 0;
	ft_close(STDIN_FILENO, STDOUT_FILENO, -1);
	while (wait_all != -1)
		wait_all = waitpid(-1, NULL, 0);
	ft_dup(data, STDIN, STDIN_FILENO);
	ft_dup(data, STDOUT, STDOUT_FILENO);
	// dup2(STDIN, STDIN_FILENO);
	// dup2(STDOUT, STDOUT_FILENO);
	// close(STDIN);
	// close(STDOUT);
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

// void	ft_std_manager(t_data *data, t_exec *exec, int STDIN, int STDOUT)
// {
// 	int	wait_all;

// 	wait_all = 0;
// 	close(STDIN_FILENO);
// 	close(STDOUT_FILENO);
// 	while (wait_all != -1)
// 		wait_all = waitpid(-1, NULL, 0);
// 	ft_dup(data, exec, STDIN, STDIN_FILENO);
// 	ft_dup(data, exec, STDOUT, STDOUT_FILENO);
// 	if (!WIFSIGNALED(g_status))
// 		g_status = WEXITSTATUS(g_status);
// 	else if (WIFSIGNALED(g_status))
// 	{
// 		if (WTERMSIG(g_status) == SIGQUIT)
// 			ft_putstr_fd("Quit (core dumped)", STDERR_FILENO);
// 		ft_putstr_fd("\n", STDERR_FILENO);
// 		g_status = 128 + WTERMSIG(g_status);
// 	}
// }

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

void	child_process(t_data *data, t_exec *exec, t_parser *parse)
{
	char	**env_tab;
	char	*cmd;

	signal(SIGINT, ft_ctrl_c_exec);
	signal(SIGQUIT, SIG_DFL);
	ft_close(exec->pipes[0], exec->fd_stdin, exec->fd_stdout);
	if (exec->flag_out != -1)
		ft_dup(data, exec->outfile, STDOUT_FILENO);
	else if (parse->next)
		ft_dup(data, exec->pipes[1], STDOUT_FILENO);
	if (parse->cmd[0] && is_builtin(data, parse))
	{
		ft_close_all(data, exec);
		ft_free_exit(data, g_status, NULL);
	}
	if (parse->cmd[0])
	{
		cmd = ft_get_cmd(data, parse);
		env_tab = get_env_tab(data);
		execve(cmd, parse->cmd, env_tab);
	}
	ft_close_all(data, exec);
	g_status = 0;
	ft_free_exit(data, g_status, NULL);
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
		if (exec->flag_out != -1)
			close(exec->outfile);
		close(exec->pipes[1]);
		if (parse->next && exec->flag_in == -1)
			ft_dup(data, exec->pipes[0], STDIN_FILENO);
		else if (parse->next)
		{
			ft_dup(data, exec->infile, STDIN_FILENO);
			close(exec->pipes[0]);
		}
	}
}

void	pipex(t_data *data, t_exec *exec)
{
	t_parser	*parse;

	exec->fd_stdin = dup(STDIN_FILENO);
	exec->fd_stdout = dup(STDOUT_FILENO);
	parse = data->parser;
	while (parse)
	{
		if (ft_set_redir(data, parse, exec) == false)
		{
			parse = parse->next;
			if (!parse)
				return ;
		}
		else
			ft_dup_manager(data, exec);
		parent_process(data, exec, parse);
		parse = parse->next;
	}
	waitpid(exec->pid, &exec->status, 0);
	g_status = exec->status;
	ft_std_manager(data, exec, exec->fd_stdin, exec->fd_stdout);
}
