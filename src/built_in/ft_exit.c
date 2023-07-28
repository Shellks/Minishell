/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:23:30 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/28 12:30:22 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_print_false_exit(t_data *data, t_exec *exec, char *cmd)
{
	ft_close(exec->fd_stdin, exec->fd_stdout, -1);
	ft_close_all(data, exec, IS_PIPE);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: `", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("': numeric argument required\n", STDERR_FILENO);
	ft_free_env(data);
	g_status = 2;
	exit (g_status);
}

static void	check_overflow_exit(t_data *data, char *cmd)
{
	int	max;
	int	last;

	max = 19;
	last = 7;
	if (cmd[0] == '-')
	{
		max++;
		last++;
	}
	if ((int)ft_strlen(cmd) >= max)
	{
		if ((int)ft_strlen(cmd) == max)
			if (cmd[ft_strlen(cmd) - 1] - '0' <= last)
				return ;
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_print_exit_error(cmd);
		ft_free_env(data);
		g_status = 2;
		exit (g_status);
	}
	return ;
}

static void	is_exit_digit(t_data *data, char *cmd, t_exec *exec)
{
	int	res;

	check_overflow_exit(data, cmd);
	res = ft_atoi(cmd);
	if (res > 255 || res < 0)
	{
		ft_close(exec->fd_stdin, exec->fd_stdout, -1);
		ft_close_all(data, exec, IS_PIPE);
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_free_env(data);
		g_status = res;
		exit (g_status);
	}
	else
	{
		ft_close(exec->fd_stdin, exec->fd_stdout, -1);
		ft_close_all(data, exec, IS_PIPE);
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_free_env(data);
		g_status = res % 256;
		exit (g_status);
	}
}

static bool	check_exit_args(t_data *data, char *cmd, t_parser *pars, t_exec *ex)
{
	data->i = 0;
	while (cmd[data->i])
	{
		if (data->i == 0 && (cmd[0] == '+' || cmd[0] == '-'))
			data->i++;
		if (cmd[data->i] >= 48 && cmd[data->i] <= 57)
			data->i++;
		else
			ft_print_false_exit(data, ex, cmd);
	}
	if (pars->cmd[1] && pars->cmd[2])
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		g_status = 1;
		return (false);
	}
	is_exit_digit(data, cmd, ex);
	return (true);
}

void	ft_exit(t_data *data, t_parser *parser, t_exec *exec)
{
	if (parser->cmd[1])
		if (check_exit_args(data, parser->cmd[1], parser, exec) == false)
			return ;
	ft_close(exec->fd_stdin, exec->fd_stdout, -1);
	ft_close_all(data, exec, IS_PIPE);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_free_env(data);
	exit(g_status);
}
