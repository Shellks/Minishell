/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_delone.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:51:50 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/07 23:00:54 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_parser_delone(t_parser *lst)
{
	int	i;

	i = 0;
	if (lst)
	{
		if (lst->cmd)
		{
			while(lst->cmd[i])
			{
				free(lst->cmd[i]);
				i++;
			}
			free(lst->cmd);
		}
		free(lst);
	}
}
