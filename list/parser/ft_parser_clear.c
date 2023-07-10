/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:51:01 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/07 11:47:48 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_parser_clear(t_parser **lst)
{
	t_parser	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		ft_redir_clear(&(*lst)->redir);
		tmp = (*lst)->next;
		ft_parser_delone(*lst);
		*lst = tmp;
	}
	*lst = 0;
}
