/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:52:17 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/19 10:06:21 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_split(t_data *data)
{
	int	i;

	i = -1;
	while(data->path[++i])
		free(data->path[i]);
	free(data->path);
}

void	ft_free(t_data	*data, int	error, char *msg, int nb)
{
	if (data->cmd_path != NULL)
		free(data->cmd_path);
	if (nb == 1)
		ft_env_clear(&data->env);
	if (nb == 2)
	{
		ft_env_clear(&data->env);
		ft_lexer_clear(&data->lexer);
	}
	printf("%s\n", msg);
	exit (error);
}
