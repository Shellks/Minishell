/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:52:17 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/19 16:37:22 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_split(t_data *data)
{
	int	i;

	i = -1;
	while (data->path[++i])
		free(data->path[i]);
	free(data->path);
}

void	ft_free(t_data *data, int error, char *msg)
{
	ft_env_clear(&data->env);
	printf("%s\n", msg);
	exit (error);
}
