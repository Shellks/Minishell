/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_add_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:03:39 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/27 12:46:40 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
		}
		else
			*lst = new;
	}
}
