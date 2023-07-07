/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:14:11 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/07 12:00:27 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_syntax_error(char *word)
{
	printf("minishell: syntax error near unexpected token `%s'\n", word);
}

void	del_node_space(t_data *data)
{
	t_lexer	*tmp1;
	t_lexer	*tmp2;

	tmp1 = data->lexer;
	while (tmp1)
	{
		if (tmp1->token == 6)
		{
			if (!tmp1->previous)
				data->lexer = data->lexer->next;
			tmp2 = tmp1->next;
			ft_lexer_delone(tmp1);
			tmp1 = tmp2;
			continue ;
		}
		tmp1 = tmp1->next;
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