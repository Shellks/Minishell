/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:55:17 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/03 19:16:32 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_lexer	*create_chained_parsing(t_data *data, t_lexer *lexer, t_parser *lst, int i)
{
	int		j;
	int		len;
	t_redir	*tmp_redir;

	len = 0;
	j = 0;
	lst->cmd = (char **)ft_calloc(sizeof(char *), (i + 1));
	if (!lst->cmd)
		ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
	lst->redir = NULL;
	while(lexer && len < i)
	{
		if (lexer->token == WORD)
		{
			lst->cmd[j] = ft_strdup(lexer->word);
			if (!lst->cmd[j])
				ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
			lexer = lexer->next;
			j++;
			len++;
		}
		else
		{
			if (lexer->next && lexer->next->token == WORD)
			{
				tmp_redir = ft_redir_new(lexer->token);
				if (!tmp_redir)
					ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
				tmp_redir->redirec = ft_strdup(lexer->next->word);
				ft_redir_add_back(&lst->redir, tmp_redir);
				if (lexer->next->next)
				{
					len += 2;
					lexer = lexer->next->next;
				}
				else
					return (lexer);
			}
			else
			{
				data->flag = 1;
				return (lexer);
			}
		}
	}
	return (lexer);
}

bool	ft_parser(t_data *data)
{
	int			i;
	t_lexer		*lexer;
	t_parser	*parser;
	t_parser	*new;

	data->parser = NULL;
	data->flag = 0;
	i = 0;
	del_node_space(data);
	lexer = data->lexer;
	new = ft_parser_new();
	if (!new)
		ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
	ft_parser_add_back(&data->parser, new);
	parser = data->parser;
	if (lexer->token == PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (FALSE);
	}
	i = count_node(lexer);
	while(lexer)
	{
		lexer = create_chained_parsing(data, lexer, parser, i);
		if (data->flag == 1)
		{
			printf("syntax error near unexpected token `newline'\n");
			return (FALSE);
		}
		if (lexer && lexer->token == PIPE && lexer->next)
		{
			if (lexer->next && lexer->next->token == PIPE)
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (FALSE);
			}
			new = ft_parser_new();
			if (!new)
				ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
			
			ft_parser_add_back(&data->parser, new);
			parser = parser->next;
			lexer = lexer->next;
			i = count_node(lexer);
		}
		else
			break ;
	}
	return (TRUE);
}
