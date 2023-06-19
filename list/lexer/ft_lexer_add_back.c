/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_add_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:48:31 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/19 10:36:14 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lexer_add_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*tmp;

	if (!new)
		return ;
	if (lst)
	{
		if (*lst)
		{
			tmp = ft_lexer_last(*lst);
			tmp->next = new;
			new->previous = tmp;
		}
		else
			*lst = new;
	}
}
