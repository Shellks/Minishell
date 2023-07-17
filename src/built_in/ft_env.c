/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:42:09 by nicolasbern       #+#    #+#             */
/*   Updated: 2023/07/17 23:49:19 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_env(t_data *data)
{
	t_env	*tmp;

	tmp = NULL;
	tmp = data->env;
	//TODO : redir le result de printf avec dup2
    // data->parser->pid = fork();
    // if (data->parser->pid == -1)
    //     exit (EXIT_FAILURE);
    // if (ft_dup_fd(data->parser))
    //     exit(EXIT_FAILURE);
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