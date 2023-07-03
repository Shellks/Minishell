/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:08:57 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/03 18:12:39 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status;

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_env	*tmp;

	(void)argv;
	g_status = 0;
	data.flag = 0;
	if (argc != 1)
	{
		//printf("error\n");
		return (0);
	}
	set_env(&data, env);
	tmp = data.env;
	while (tmp)
	{
		printf("%s : %s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
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
