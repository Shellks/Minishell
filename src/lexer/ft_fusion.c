/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fusion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:06:43 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/27 00:02:13 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_del_dollar(t_data *data)
{
	t_lexer	*cur;

	cur = data->lexer;
	while (cur && cur->next)
	{
		if (cur->token == WORD && cur->next->token == WORD)
			if (cur->word && cur->word[0] == '$' && !cur->word[1])
			{
				ft_lexer_delone(cur);
				if (data->lexer == cur && !data->lexer->previous)
					data->lexer = data->lexer->next;
			}
		cur = cur->next;
	}	
}

void	ft_fusion(t_data *data)
{
	t_lexer	*cur;
	char	*str;

	ft_del_dollar(data);
	cur = data->lexer;
	while (cur && cur->next)
	{
		if (cur->token == WORD && cur->next->token == WORD)
		{
			if (cur->quote == NONE && cur->next->quote != NONE)
				cur->quote = cur->next->quote;
			str = ft_strjoin(cur->word, cur->next->word);
			if (!str)
				ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
			free(cur->word);
			cur->word = str;
			ft_lexer_delone(cur->next);
		}
		else
			cur = cur->next;
	}
}
