/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:22:29 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/25 23:39:15 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

 #include "../../include/minishell.h"

// // static void	cmd_is_builtin(t_data *data, t_exec *exec, t_parser *parse)
// // {
// // 	if (parse->cmd[0] && is_builtin(data, parse))
// // 	{
// // 		if (exec->flag_in != -1)
// // 			close(exec->infile);
// // 		if (exec->flag_out != -1)
// // 			close(exec->outfile);
// // 		ft_free_exit(data, g_status, NULL);
// // 	}
// // }



// static void	child_without_pipe(t_data *data, t_exec *exec, t_parser *parse)
// {
// 	char	**env_tab;
// 	char	*cmd;

// 	signal(SIGQUIT, SIG_DFL);
// 	signal(SIGINT, ft_ctrl_c_exec);
// 	cmd = NULL;
// 	env_tab = NULL;
// 	ft_close(exec->fd_stdin, exec->fd_stdout, -1);
// 	if (exec->flag_out != -1)
// 		ft_dup(data, exec->outfile, STDOUT_FILENO);
// 	if (parse->cmd[0])
// 	{
// 		cmd = ft_get_cmd(data, parse);
// 		env_tab = get_env_tab(data);
// 		execve(cmd, parse->cmd, env_tab);
// 	}
// 	ft_close(STDIN_FILENO, STDOUT_FILENO, -1);
// 	ft_exit_execve_fail(data, exec, cmd, env_tab);
// }

// void	exec_simple_cmd(t_data *data, t_exec *exec)
// {
// 	t_parser	*parse;

// 	signal(SIGINT, SIG_IGN);
// 	parse = data->parser;
// 	if (data->parser->cmd[0])
// 		ft_dup_manager(data, exec);
// 	// if (parse->cmd[0] && is_builtin(data, parse))
// 	// {
// 	// 	ft_close(exec->fd_stdin, exec->fd_stdout, -1);
// 	// 	ft_close(STDIN_FILENO, STDOUT_FILENO, -1);
// 	// 	ft_exit_minishell(data, exec, IS_NOT_PIPE);
// 	// }
// 	exec->pid = fork();
// 	if (exec->pid == -1)
// 		ft_free_exit(data, ERR_FORK, "Error with creating fork\n");
// 	if (exec->pid == 0)
// 		child_without_pipe(data, exec, parse);
// 	waitpid(exec->pid, &g_status, 0);
// 	ft_std_manager(data, exec->fd_stdin, exec->fd_stdout);
// 	ft_close_all(data, exec, IS_NOT_PIPE);
// 	ft_close(exec->fd_stdin, exec->fd_stdout, -1);
// }
