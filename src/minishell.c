/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:08:57 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/27 14:40:44 by nibernar         ###   ########.fr       */
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

void	ft_exec(t_data *data, t_exec *exec)
{
	if (ft_built_in_process(data, exec) == true)
		return ;
	exec->pid = fork();
	if (exec->pid == -1)
		ft_free_exit(data, ERR_FORK, "Error with creating fork\n");
	if (exec->pid == 0)
	{
		pipex(data, exec);
		ft_close_all(data, exec, IS_PIPE);
		ft_close(exec->fd_stdin, exec->fd_stdout, -1);
		ft_close(STDIN_FILENO, STDOUT_FILENO, -1);
		ft_free_exit(data, g_status, NULL);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(exec->pid, &g_status, 0);
		g_status = WEXITSTATUS(g_status);
	}
}

void	ft_mini_loop(t_data *data, t_exec *exec)
{
	t_lexer	*check_space;

	check_space = data->lexer;
	if (data->input[0])
		add_history(data->input);
	if (lexer(data) == false)
		return ;
	if (!data->lexer)
		return ;
	ft_fusion(data);
	if (!data->lexer)
		return ;
	if (ft_parser(data) == false)
		return ;
	ft_exec(data, exec);
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
