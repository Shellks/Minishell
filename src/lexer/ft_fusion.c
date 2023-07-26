/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fusion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:06:43 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/26 16:40:18 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	ft_del_dollar(t_data *data)
// {
// 	t_lexer	*cur;

// 	cur = data->lexer;
// 	while (cur && cur->next)
// 	{
// 		if (cur->token == WORD && cur->next->token == WORD)
// 			if (cur->word && cur->word[0] == '$' && !cur->word[1])
// 				ft_lexer_delone(cur);
// 		cur = cur->next;
// 	}	
// }

void	ft_fusion(t_data *data)
{
	t_lexer	*cur;
	char	*str;

	//ft_del_dollar(data);
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
