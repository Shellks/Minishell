/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:42:09 by nicolasbern       #+#    #+#             */
/*   Updated: 2023/07/20 18:14:41 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_env(t_data *data)
{
	t_env	*tmp;

	tmp = NULL;
	tmp = data->env;
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
