/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_add_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:03:39 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/03 14:41:53 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_redir_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

	if (!new)
		return ;
	if (lst)
	{
		if (*lst)
		{
			tmp = ft_redir_last(*lst);
			tmp->next = new;
			new->previous = tmp;
		}
		else
			*lst = new;
	}
}
