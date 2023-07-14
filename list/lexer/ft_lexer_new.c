/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:57:28 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/12 13:43:13 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_lexer	*ft_lexer_new(char *word, t_token token, t_quote quote)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (0);
	new->word = word;
	new->token = token;
	new->quote = quote;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}


