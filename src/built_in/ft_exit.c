/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:23:30 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/27 13:21:42 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static void	is_exit_digit(t_data *data, char *cmd)
{
	int	res;

	check_overflow_exit(data, cmd);
	res = ft_atoi(cmd);
	if (res > 255 || res < 0)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_free_env(data);
		g_status = res;
		exit (g_status);
	}
	else
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_free_env(data);
		g_status = res % 256;
		exit (g_status);
	}
}

static bool	check_exit_args(t_data *data, char *cmd, t_parser *parser)
{
	int	j;

	j = 0;
	while (cmd[j])
	{
		if (j == 0 && (cmd[0] == '+' || cmd[0] == '-'))
			j++;
		if (cmd[j] >= 48 && cmd[j] <= 57)
			j++;
		else
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			ft_putstr_fd("minishell: exit: `", STDERR_FILENO);
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putstr_fd("': numeric argument required\n", STDERR_FILENO);
			ft_free_env(data);
			g_status = 2;
			exit (g_status);
		}
	}
	if (parser->cmd[1] && parser->cmd[2])
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
		g_status = 1;
		return (false);
	}
	//dprintf(2, "g_status = %d\n", g_status);
	is_exit_digit(data, cmd);
	return (true);
}

void	ft_exit(t_data *data, t_parser *parser)
{
	if (parser->cmd[1])
		if (check_exit_args(data, parser->cmd[1], parser) == false)
			return ;
	//dprintf(2, "g_status = %d\n", g_status);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_free_env(data);
	exit(g_status);
}
