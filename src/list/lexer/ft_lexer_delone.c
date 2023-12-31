/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_delone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:51:50 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/27 12:50:48 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_lexer_delone(t_lexer *lst)
{
	if (lst)
	{
		if (lst->word)
			free(lst->word);
		if (lst->previous)
			lst->previous->next = lst->next;
		if (lst->next)
			lst->next->previous = lst->previous;
		free(lst);
	}
}
