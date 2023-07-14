/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:08:57 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/13 19:40:13 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status;

bool	get_built_in(t_data *data)
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

void	ft_exec(t_data *data, t_exec *exec)
{
	if (!data->parser->next)
	{
		ft_set_redir(data, data->parser, exec);
		if (data->parser->cmd[0] && !data->parser->next)
			if (get_built_in(data) == false)
				return ;
		return ;
	}
	ft_set_redir(data, data->parser, exec);
	pipex(data, exec);
}

void	ft_mini_loop(t_data *data, t_exec *exec)
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
 	//print_parser(&data->parser);
	ft_exec(data, exec);
}

static bool	init_var(t_data	*data, t_exec *exec, char **env, int argc)
{
	if (argc != 1)
	{
		printf("minishell: error: no args expected\n");
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
	exec->flag_in = 0;
	exec->flag_out = 0;
	set_env(data, env);
	return (true);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	//t_env	*tmp;
	t_exec	exec;

	(void)argv;
	if (init_var(&data, &exec, env, argc) == false)
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
		data.input = readline(COLOR"Minishell > "RESET);
		if (!data.input)
		{
			printf("exit\n");
			ft_free_env(&data);
			return (0);
		}
		ft_mini_loop(&data, &exec);
		ft_free_loop(&data);
	}
	ft_free_env(&data);
	return (0);
}
