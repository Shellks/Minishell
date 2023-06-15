/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:08:57 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/15 11:50:37 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_env	*tmp;
	int	i;

	//env[0] = NULL;
	if (argc != 2)
	{
		//printf("error\n");
		return (0);
	}
	
	parsing(&data, argv, env);
	while (1)
	{
		data.input = readline("Minishell > ");
		add_history(data.input);
		//dprintf(2, "|%s|\n", data.input);
		free (data.input);
	}
	tmp = data.env;
	while (tmp)
	{
		printf("%s : %s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
	i = -1;
	if (data.path)
	{
		while (data.path[++i])
			printf("path_line[%d] : %s\n", i, data.path[i]);
		ft_free_split(&data);
	}
	ft_env_clear(&data.env);
}
