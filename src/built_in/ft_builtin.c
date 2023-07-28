/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:10:21 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/28 12:10:08 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(t_data *data, t_parser *parse, t_exec *exec)
{
	int	len;

	len = 0;
	if (!ft_strncmp(parse->cmd[0], "pwd", 3) && \
	(int)ft_strlen(parse->cmd[0]) == 3 && ++len)
		ft_pwd();
	else if (!ft_strncmp(parse->cmd[0], "unset", 5) && \
	(int)ft_strlen(parse->cmd[0]) == 5 && ++len)
		ft_unset(data, parse);
	else if (!ft_strncmp(parse->cmd[0], "export", 6) && \
	(int)ft_strlen(parse->cmd[0]) == 6 && ++len)
		ft_export(data, parse);
	else if (!ft_strncmp(parse->cmd[0], "exit", 4) && \
	(int)ft_strlen(parse->cmd[0]) == 4 && ++len)
		ft_exit(data, parse, exec);
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

static bool	check_is_builtin(t_parser *parse)
{
	if (!ft_strncmp(parse->cmd[0], "pwd", 3) && \
	(int)ft_strlen(parse->cmd[0]) == 3)
		return (true);
	else if (!ft_strncmp(parse->cmd[0], "unset", 5) && \
	(int)ft_strlen(parse->cmd[0]) == 5)
		return (true);
	else if (!ft_strncmp(parse->cmd[0], "export", 6) && \
	(int)ft_strlen(parse->cmd[0]) == 6)
		return (true);
	else if (!ft_strncmp(parse->cmd[0], "exit", 4) && \
	(int)ft_strlen(parse->cmd[0]) == 4)
		return (true);
	else if (!ft_strncmp(parse->cmd[0], "env", 3) && \
	(int)ft_strlen(parse->cmd[0]) == 3)
		return (true);
	else if (!ft_strncmp(parse->cmd[0], "echo", 4) && \
	(int)ft_strlen(parse->cmd[0]) == 4)
		return (true);
	else if (!ft_strncmp(parse->cmd[0], "cd", 2) && \
	(int)ft_strlen(parse->cmd[0]) == 2)
		return (true);
	return (false);
}

bool	ft_built_in_process(t_data *data, t_exec *exec)
{
	t_parser	*parse;

	parse = data->parser;
	if (!parse->next && parse->cmd[0] && check_is_builtin(parse))
	{
		exec->fd_stdin = dup(STDIN_FILENO);
		exec->fd_stdout = dup(STDOUT_FILENO);
		ft_set_redir(data, parse, exec);
		if (exec->flag_in == -2 || exec->flag_out == -2)
		{
			g_status = 1;
			return (ft_close(exec->fd_stdin, exec->fd_stdout, -1), true);
		}
		ft_dup_manager(data, exec);
		if (exec->flag_out == 1)
			ft_dup(data, exec->outfile, STDOUT_FILENO);
		is_builtin(data, parse, exec);
		if (exec->flag_in > 0)
			ft_dup(data, exec->fd_stdin, STDIN_FILENO);
		if (exec->flag_out == 1)
			ft_dup(data, exec->fd_stdout, STDOUT_FILENO);
		return (ft_close(exec->fd_stdin, exec->fd_stdout, -1), true);
	}
	return (false);
}
