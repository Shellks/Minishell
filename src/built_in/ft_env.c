/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:42:09 by nicolasbern       #+#    #+#             */
/*   Updated: 2023/07/21 15:00:51 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_env(t_data *data)
{
	t_env	*tmp;

	tmp = ft_env_first(data->env);
	while (tmp)
	{
		if (tmp->equals != NOT_EQUALS)
		{
			ft_putstr_fd(tmp->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(tmp->content, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
	return (true);
}
