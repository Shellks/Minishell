/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_add_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:48:31 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/14 18:06:04 by nibernar         ###   ########.fr       */
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