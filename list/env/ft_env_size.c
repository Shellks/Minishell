/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:20:41 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/15 10:25:38 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
