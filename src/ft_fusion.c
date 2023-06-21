/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fusion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:06:43 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/21 18:42:21 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_fusion(t_data *data)
{
	t_lexer	*cur;
	char	*str;
	int		i;

	cur = data->lexer;
	i = 0;
	while(cur && cur->next)
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
		if (cur->next->token != WORD)
			break ;
	}
}
