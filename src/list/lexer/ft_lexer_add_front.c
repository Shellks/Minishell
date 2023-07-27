/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_add_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:49:53 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/27 12:50:36 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_lexer_add_front(t_lexer **lst, t_lexer *new)
{
	if (!new)
		return ;
	*lst = ft_lexer_first(*lst);
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
