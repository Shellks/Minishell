/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:51:01 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/27 12:46:24 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
