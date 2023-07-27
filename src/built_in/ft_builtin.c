/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:10:21 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/27 14:25:56 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	check_is_builtin(t_parser *parse)
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
		is_builtin(data, parse);
		if (exec->flag_in > 0)
			ft_dup(data, exec->fd_stdin, STDIN_FILENO);
		if (exec->flag_out == 1)
			ft_dup(data, exec->fd_stdout, STDOUT_FILENO);
		return (ft_close(exec->fd_stdin, exec->fd_stdout, -1), true);
	}
	return (false);
}
