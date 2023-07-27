/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:20:41 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/27 12:50:27 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_env_size(t_env *lst)
{
	int	size;

	size = 0;
	lst = ft_env_first(lst);
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
