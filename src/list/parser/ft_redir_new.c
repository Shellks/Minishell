/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:02:09 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/27 12:46:56 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_redir	*ft_redir_new(t_token token, t_quote quote)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new->quote = quote;
	new->redirec = NULL;
	new->token = token;
	new->next = NULL;
	return (new);
}
