/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_add_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:57:08 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/27 12:50:01 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
