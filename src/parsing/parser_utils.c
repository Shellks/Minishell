/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:14:11 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/06 16:13:50 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_syntax_error(char *word)
{
	printf("minishell: syntax error near unexpected token `%s'\n", word);
}

void	del_node_space(t_data *data)
{
	t_lexer	*tmp;

	tmp = ft_lexer_first(data->lexer);
	while (tmp)
	{
		if (tmp->token == 6)
		{
			if (!tmp->previous)
				data->lexer = data->lexer->next;
			ft_lexer_delone(tmp);
		}
		tmp = tmp->next;
	}
}

int		count_node(t_lexer	*lexer)
{
	t_lexer	*tmp;
	int	i;

	i = 0;
	tmp = lexer;
	while(tmp && tmp->token != PIPE)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}