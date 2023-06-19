/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:08:57 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/19 16:36:12 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parser(t_data *data)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = data->lexer;
	data->pipe = 0;
	while (tmp->next)
	{
		if (tmp->token == PIPE)
			data->pipe++;
		tmp = tmp->next;
	}
	dprintf(2, "pipe : %d\n", data->pipe);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_env	*tmp;
	int		i;

	if (argc != 1)
	{
		//printf("error\n");
		return (0);
	}
	parsing(&data, argv, env);
	while (1)
	{
		data.input = readline("Minishell > ");
		add_history(data.input);
		lexer(&data);
		parser(&data);
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
