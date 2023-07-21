/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:23:30 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/20 18:13:13 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	is_exit_digit(t_data *data, int i)
{
	int	res;

	res = ft_atoi(data->parser->cmd[i]);
	if (res > 255 || res < 0)
	{
		ft_free_env(data);
		exit (res % 256);
	}
	else
	{
		ft_free_env(data);
		exit (res);
	}
}

static void	check_exit_args(t_data *data, t_parser *cur, int i)
{
	int	j;

	j = 0;
	while (cur->cmd[i][j])
	{
		if (cur->cmd[i][j] >= 48 && data->parser->cmd[i][j] <= 57)
			j++;
		else
		{
			printf("minishell: exit: %s: digital arguments \
					required\n", cur->cmd[i]);
			ft_free_env(data);
			exit (2);
		}
	}
	is_exit_digit(data, i);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = 1;
	if (data->parser->cmd[i])
		check_exit_args(data, data->parser, i);
	ft_free_env(data);
	exit (g_status);
}
