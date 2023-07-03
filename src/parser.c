/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:55:17 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/03 20:54:10 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	parse_redir(t_data *data, t_lexer **lex, t_parser *lst, int *i)
{
	t_redir *redir;

	if ((*lex)->next && (*lex)->next->token == WORD)
	{
		redir = ft_redir_new((*lex)->token);
		if (!redir)
			ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
		redir->redirec = ft_strdup((*lex)->next->word);
		ft_redir_add_back(&lst->redir, redir);
		if ((*lex)->next->next)
		{
			(*i) += 2;
			*lex = (*lex)->next->next;
		}
		else
			return (false);
	}
	else
	{
		data->flag = 1;
		return (false);
	}
	return (true);
}

static t_lexer	*parse_cmd(t_data *data, t_lexer *lexer, t_parser *lst, int i)
{
	int		j;
	int		len;

	len = 0;
	j = -1;
	lst->cmd = (char **)ft_calloc(sizeof(char *), (i + 1));
	if (!lst->cmd)
		ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
	lst->redir = NULL;
	while(lexer && len < i)
	{
		if (lexer->token == WORD)
		{
			lst->cmd[++j] = ft_strdup(lexer->word);
			if (!lst->cmd[j])
				ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
			lexer = lexer->next;
			len++;
		}
		else
			if (parse_redir(data, &lexer, lst, &len) == false)
				return (lexer);
	}
	return (lexer);
}
int	parser_loop(t_data *data, t_lexer *lexer, t_parser *parser, int i)
{
	t_parser *new;

	while(lexer)
	{
		lexer = parse_cmd(data, lexer, parser, i);
		if (data->flag == 1)
			return (ft_print_syntax_error("newline"), FALSE);
		if (lexer && lexer->token == PIPE && lexer->next)
		{
			if (lexer->next && lexer->next->token == PIPE)
				return (ft_print_syntax_error("|"), FALSE);
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
		return (ft_print_syntax_error("newline"), FALSE);
	i = count_node(lexer);
	if (parser_loop(data, lexer, parser, i) == FALSE)
		return (FALSE);
	return (TRUE);
}
