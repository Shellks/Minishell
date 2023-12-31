/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 18:01:00 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/27 12:45:35 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_lexer_size(t_lexer *lst)
{
	int	size;

	size = 0;
	lst = ft_lexer_first(lst);
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
