/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_delone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:32:36 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/20 18:30:18 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env_delone(t_env *lst)
{
	if (lst)
	{
		if (lst->previous)
			lst->previous->next = lst->next;
		if (lst->next)
			lst->next->previous = lst->previous;
		if (lst->name)
			free(lst->name);
		if (lst->content)
			free(lst->content);
		free(lst);
	}
}
