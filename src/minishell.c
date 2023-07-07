/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:08:57 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/08 00:12:42 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status;

bool	exec_built_in(t_data *data)
{
	if (ft_strncmp(data->parser->cmd[0], "pwd", 3) == 0)
	{
		printf("%s\n", data->pwd->content);
		return (false);
	}
	else if (ft_strncmp(data->parser->cmd[0], "unset", 5) == 0)
	{
		if (ft_unset(data, data->parser) == false)
			return (false);
	}
	else if (ft_strncmp(data->parser->cmd[0], "export", 6) == 0)
	{
		if (ft_export(data, data->parser) == false)
			return (false);
	}
	else if (ft_strncmp(data->parser->cmd[0], "exit", 4) == 0)
		ft_exit(data);
	return (true);
}

void	ft_mini_loop(t_data *data)
{
	add_history(data->input);
 	if (lexer(data) == false)
		return ;
	if (!data->lexer)
		return ;
 	ft_fusion(data);
 	//print_lexer(&data->lexer);
	if (ft_parser(data) == false)
		return ;
 	print_parser(&data->parser);
	if (data->parser->cmd[0] || !data->parser->next)
		if (exec_built_in(data) == false)
			return ;
}

static bool	init_var(t_data	*data, char **env, int argc)
{
	if (argc != 1)
	{
		printf("minishell: error: no args expect\n");
		return (false);
	}
	g_status = 0;
	data->flag = 0;
	data->count = 0;
	data->env = NULL;
	data->path = NULL;
	data->lexer = NULL;
	data->input = NULL;
	data->parser = NULL;
	set_env(data, env);
	return (true);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
//	t_env	*tmp;

	(void)argv;
	if (init_var(&data, env, argc) == false)
		return (1);
	// tmp = data.env;
	// while (tmp)
	// {
	// 	printf("%s=%s\n", tmp->name, tmp->content);
	// 	tmp = tmp->next;
	// }
	//niveau malloc tout est ok reste juste les 4 sortie de exit qui sont chelou!!!!!
	while (1)
	{
		//	deuxieme boucle d'env pour faire des checks si besoin
		// tmp = data.env;
		// while (tmp)
		// {
		// 	printf("%s=%s\n", tmp->name, tmp->content);
		// 	tmp = tmp->next;
		// }
		data.input = readline(COLOR"Minishell > "RESET);
		if (!data.input)
		{
			printf("exit\n");
			ft_free_env(&data);
			return (0);
		}
		ft_mini_loop(&data);
		ft_free_loop(&data);
	}
	ft_free_env(&data);
	return (0);
}
