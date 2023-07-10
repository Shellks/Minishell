/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbernard <nicolasbernard@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:08:57 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/10 07:56:45 by nicolasbern      ###   ########.fr       */
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
	else if (ft_strncmp(data->parser->cmd[0], "env", 3) == 0)
	{
		if (ft_env(data) == false)
			return (false);
	}
	else if (ft_strncmp(data->parser->cmd[0], "echo", 4) == 0)
	{
		if (ft_echo(data) == false)
			return (false);
	}
	else if (ft_strncmp(data->parser->cmd[0], "cd", 2) == 0)
	{
		if (ft_cd(data ,data->parser->cmd) == false)
			return (false);
	}
	return (true);
}

void	ft_mini_loop(t_data *data)
{
	add_history(data->input);
 	lexer(data);
	if (!data->lexer)
		return ;
 	ft_fusion(data);
 	//print_lexer(&data->lexer);
	if (ft_parser(data) == false)
		return ;
 	//print_parser(&data->parser);
	if (!data->parser->next)
		if (exec_built_in(data) == false)
			return ;
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
//	t_env	*tmp;

	(void)argv;
	g_status = 0;
	data.flag = 0;
	//cette init parser permet d'annuler un conditional jump si juste des 
	//espaces dans data.input, a voir si on ferait pas 
	//une vrai init propre ou si on laisse comme ça
	data.parser = NULL;
	if (argc != 1)
	{
		printf("error args : try again with only arg : ./minishell\n");
		return (0);
	}
	set_env(&data, env);
	// tmp = data.env;
	// while (tmp)
	// {
	// 	printf("%s=%s\n", tmp->name, tmp->content);
	// 	tmp = tmp->next;
	// }
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
		if (data.lexer)
			ft_lexer_clear(&data.lexer);
		if (data.parser)
			ft_parser_clear(&data.parser);
		free (data.input);
	}
	ft_free_env(&data);
}
