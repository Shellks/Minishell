/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_first.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:22:01 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/27 12:50:16 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_env	*ft_env_first(t_env *lst)
{
	if (!lst)
		return (0);
	while (lst->previous)
		lst = lst->previous;
	return (lst);
}
