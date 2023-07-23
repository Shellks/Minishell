/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:08:57 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/23 17:59:03 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status;

t_data	*ft_get_data(t_data *data)
{
	static t_data	*data_ptr;

	if (data)
		data_ptr = data;
	return (data_ptr);
}

void	pipex_no_pipe(t_data *data, t_exec *exec)
{
	if (ft_set_redir(data, data->parser, exec) == false)
		return ;
	if (data->parser->cmd[0])
	{
		if (ft_strncmp(data->parser->cmd[0], "cd", 2) == 0)
		{
			ft_cd(data, data->parser->cmd);
			return ;
		}
		else if (!ft_strncmp(data->parser->cmd[0], "export", 6))
		{
			g_status = ft_export(data, data->parser);
			return ;
		}
		else if (!ft_strncmp(data->parser->cmd[0], "unset", 5))
		{
			g_status = ft_unset(data, data->parser);
			return ;
		}
		else if (ft_strncmp(data->parser->cmd[0], "exit", 4) == 0)
			ft_exit(data);
		exec_simple_cmd(data, exec);
	}
}

void	ft_mini_loop(t_data *data, t_exec *exec)
{
	if (data->input[0])
		add_history(data->input);
	if (lexer(data) == false)
		return ;
	if (!data->lexer)
		return ;
	ft_fusion(data);
	if (ft_parser(data) == false)
		return ;
	if (!data->parser->next)
		pipex_no_pipe(data, exec);
	else
		pipex(data, exec);
}

static bool	init_var(t_data	*data, t_exec *exec, char **env, int argc)
{
	if (argc != 1)
	{
		printf("minishell: error: no args expected\n");
		return (false);
	}
	data->flag = 0;
	data->count = 0;
	data->env = NULL;
	data->path = NULL;
	data->lexer = NULL;
	data->input = NULL;
	data->parser = NULL;
	exec->flag_in = 0;
	exec->flag_out = 0;
	ft_get_data(data);
	set_env(data, env);
	return (true);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_exec	exec;

	g_status = 0;
	(void)argv;
	if (init_var(&data, &exec, env, argc) == false)
		return (1);
	while (1)
	{
		signal(SIGINT, ft_ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		data.input = readline(COLOR"Minishell > "RESET);
		if (!data.input)
		{
			printf("Exit\n");
			ft_free_env(&data);
			return (0);
		}
		ft_mini_loop(&data, &exec);
		ft_free_loop(&data);
	}
	ft_free_env(&data);
	return (0);
}
