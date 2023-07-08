/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbernard <nicolasbernard@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:08:57 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/07 01:03:22 by nicolasbern      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status;

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	g_status = 0;
	data.flag = 0;
	if (argc != 1)
	{
		//printf("error\n");
		return (0);
	}
	set_env(&data, env);
	while (1)
	{
		data.input = readline(COLOR"Minishell > "RESET);
		if (!data.input)
		{
			printf("exit\n");
			ft_env_clear(&data.env);
			return (0);
		}
		add_history(data.input);
		lexer(&data);
		free (data.input);
	}
	ft_env_clear(&data.env);
}
