/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_first.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:53:48 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/14 18:09:26 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_lexer	*ft_lexer_first(t_lexer *lst)
{
	if (!lst)
		return (0);
	while (lst->previous)
		lst = lst->previous;
	return (lst);
}