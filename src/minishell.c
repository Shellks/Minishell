/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:08:57 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/23 15:21:44 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parser(t_data *data)
{
	t_lexer	*tmp;

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
//du coup j'ai la fonction lexer. j'arrive a creer une liste chainee. j'arrive a rentrer le token et la string de l commende mais je fait 0 check si l'argument que je rentre dans ma liste chainee est valide

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_env	*tmp;
//	int		i;

	if (argc != 1)
	{
		//printf("error\n");
		return (0);
	}
	parsing(&data, argv, env);
	tmp = data.env;
	while (tmp)
	{
		printf("%s : %s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
// 	i = -1;
// 	if (data.path)
// 	{
// 		while (data.path[++i])
// 			printf("path_line[%d] : %s\n", i, data.path[i]);
// //		ft_free_split(&data);
// 	}
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
		//dprintf(2, "|%s|\n", data.input);
		free (data.input);
	}
	ft_env_clear(&data.env);
}
