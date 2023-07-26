/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:57:28 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/26 13:15:36 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_parser	*ft_parser_new(void)
{
	t_parser	*new;

	new = malloc(sizeof(t_parser));
	if (!new)
		return (0);
	new->sign = 0;
	new->cmd = NULL;
	new->next = NULL;
	new->redir = NULL;
	return (new);
}
