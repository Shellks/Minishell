/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:57:28 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/03 16:28:17 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_parser	*ft_parser_new()
{
	t_parser	*new;

	new = malloc(sizeof(t_parser));
	if (!new)
		return (0);
	new->cmd = NULL;
	new->next = NULL;
	new->redir = NULL;
	return (new);
}
