/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_add_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:57:08 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/15 10:25:54 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env_add_front(t_env **lst, t_env *new)
{
	if (!new)
		return ;
	*lst = ft_env_first(*lst);
	if (lst)
	{
		if (*lst)
		{
			new->next = *lst;
			(*lst)->previous = new;
		}
		*lst = new;
	}
}
