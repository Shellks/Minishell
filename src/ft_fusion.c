/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fusion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:06:43 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/24 17:55:25 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_fusion(t_lexer **lexer, t_data *data)
{
	t_lexer	*cur;
	char	*str;

	cur = NULL;
	cur = *lexer;
	while(cur)
	{
		if (cur->token == WORD && cur->next->token == WORD)
		{
			str = ft_strjoin(cur->word, cur->next->word);
			if (!str)
				ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
			free(cur->word);
			cur->word = str;
			ft_lexer_delone(cur->next);
		}
		if (cur->next == NULL || cur->next->token != WORD)
		{
			break ;
		}
		cur = cur->next;
	}
}

// probleme quand on commence pas un espace
// void	ft_fusion(t_data *data)
// {
// 	t_lexer	*cur;
// 	char	*str;

// 	cur = data->lexer;
// 	while(cur && cur->next)
// 	{
// 		if (cur->token == WORD && cur->next->token == WORD)
// 		{
// 			str = ft_strjoin(cur->word, cur->next->word);
// 			if (!str)
// 				ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
// 			free(cur->word);
// 			cur->word = str;
// 			ft_lexer_delone(cur->next);
// 		}
// 		dprintf(2, "pipi %d, %u, %s\n",cur->index, cur->token, cur->word);
// 		if (cur->next == NULL || cur->next->token != WORD)
// 		{
// 			break ;
// 		}
// 	}
// }
