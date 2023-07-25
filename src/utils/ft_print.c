/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 08:13:38 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/26 00:45:24 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_exit_error(char *cmd)
{
	ft_putstr_fd("minishell: exit: `", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("': numeric argument required\n", STDERR_FILENO);
}

void	ft_print_export_error(char *cmd)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

void	ft_print_fd(char *cmd, char *msg)
{
	ft_putstr_fd("command ", STDERR_FILENO);
	if (ft_strlen(cmd) == 0)
	{
		ft_putstr_fd("''", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
	}
}

void	ft_print_fds(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (ft_strlen(cmd) == 0)
	{
		ft_putstr_fd("''", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
	}
}
