/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 08:13:38 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/25 15:19:11 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_export_error(char *word)
{
	printf("minishell: export: « %s »: invalid identifier\n", word);
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
