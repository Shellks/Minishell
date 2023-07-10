/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:52:17 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/10 13:04:24 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_split(t_data *data)
{
	int	i;

	i = 0;
	while (data->path[i])
		free(data->path[i++]);
	free(data->path);
}

void	free_exit_env(t_data *data, char *name, char *content, int i)
{
	if (i == 1)
		free (name);
	if (i == 2)
	{
		free(name);
		free(content);
	}
	ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
}

void	ft_free_exit(t_data	*data, int	error, char *msg)
{
	if (data->input)
		free(data->input);
	if (data->path)
		ft_free_split(data);
	if (data->env)
		ft_env_clear(&data->env);
	if (data->lexer)
		ft_lexer_clear(&data->lexer);
	if (data->parser)
		ft_parser_clear(&data->parser);
	if (msg)
		printf("%s\n", msg);
	exit (error);
}

void	ft_free_env(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->path)
		ft_free_split(data);
	if (data->env)
		ft_env_clear(&data->env);
	if (data->lexer)
		ft_lexer_clear(&data->lexer);
	if (data->parser)
		ft_parser_clear(&data->parser);
}

void	ft_free_loop(t_data *data)
{
	if (data->lexer)
		ft_lexer_clear(&data->lexer);
	if (data->parser)
		ft_parser_clear(&data->parser);
	free (data->input);
}
