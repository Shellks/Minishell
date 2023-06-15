/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:57:28 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/14 18:00:49 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_lexer	*ft_lexer_new(char *word, e_token token, int index)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (0);
	new->word = word;
	new->token = token;
	new->index = index;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}