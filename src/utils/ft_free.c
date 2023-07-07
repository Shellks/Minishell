/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:52:17 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/07 12:08:21 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_split(t_data *data)
{
	int	i;

	i = -1;
	while (data->path[++i])
		free(data->path[i]);
	free(data->path);
}

void	ft_free(t_data	*data, int	error, char *msg, int nb)
{
	int	i;

	i = -1;
	(void)nb;
	if (data->path)
	{
		while (data->path[++i])
			free(data->path[i]);
		free(data->path);
	}
	// if (data->cmd_path != NULL)
	// 	free(data->cmd_path);
	if (data->env)
		ft_env_clear(&data->env);
	if (data->lexer)
		ft_lexer_clear(&data->lexer);
	if (data->parser)
		ft_parser_clear(&data->parser);
	printf("%s\n", msg);
	exit (error);
}

void	ft_free_env(t_data *data)
{
	int	i;

	i = -1;
	if (data->path)
	{
		while (data->path[++i])
			free(data->path[i]);
		free(data->path);
	}
	ft_env_clear(&data->env);
	ft_lexer_clear(&data->lexer);
	if (data->parser)
		ft_parser_clear(&data->parser);
}
// void	ft_free_lexer(t_data *data)
// {
	
// }
