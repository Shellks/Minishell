/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:52:17 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/15 10:50:26 by acarlott         ###   ########lyon.fr   */
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

void	ft_free(t_data	*data, int	error, char *msg)
{
	ft_env_clear(&data->env);
	printf("%s\n", msg);
	exit (error);
}
