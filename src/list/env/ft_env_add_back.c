/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_add_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:12:46 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/27 12:49:56 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_env_add_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (lst)
	{
		if (*lst)
		{
			tmp = ft_env_last(*lst);
			tmp->next = new;
			new->previous = tmp;
		}
		else
			*lst = new;
	}
}
