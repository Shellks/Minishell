/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fusion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:06:43 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/27 13:49:13 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_del_empty_node(t_data *data)
{
	t_lexer	*cur;
	t_lexer *tmp;
	int		redir_flag;
	int		pipe_flag;

	cur = data->lexer;
	pipe_flag = 0;
	redir_flag = 0;
	while (cur)
	{
		if (cur->previous && cur->token == PIPE)
			pipe_flag = 1;
		if (cur->token >= 2 && cur->token <= 5)
			redir_flag = 1;
		if (cur->token == WORD && redir_flag != 1)
		{
			if (cur->quote == NONE && !cur->word[0] && pipe_flag == 0)
			{
				if (!cur->previous)
					data->lexer = data->lexer->next;
				tmp = cur->next;
				ft_lexer_delone(cur);
				cur = tmp;
				while (cur && cur->token == DELIMITER)
					cur = cur->next;
				if (cur && cur->token == PIPE)
				{
					if (!cur->previous)
						data->lexer = data->lexer->next;
					tmp = cur->next;
					ft_lexer_delone(cur);
					cur = tmp;
				}
				pipe_flag = 0;
				redir_flag = 0;
				continue ;
			}
		}
		cur = cur->next;
	}
}

void	ft_del_dollar(t_data *data)
{
	t_lexer	*cur;
	t_lexer *tmp;

	cur = data->lexer;
	while (cur && cur->next)
	{
		if (cur->token == WORD && cur->next->token == WORD)
		{
			if (cur->word && cur->word[0] == '$' && !cur->word[1] && \
			cur->quote == NONE)
			{
				if (!cur->previous)
					data->lexer = data->lexer->next;
				tmp = cur->next;
				ft_lexer_delone(cur);
				cur = tmp;
				continue ;
			}
		}
		cur = cur->next;
	}
}

void	ft_fusion(t_data *data)
{
	t_lexer	*cur;
	char	*str;

	
	ft_del_dollar(data);
	ft_del_empty_node(data);
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
