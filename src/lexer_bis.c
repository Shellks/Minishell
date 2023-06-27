/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:31:26 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/27 11:54:26 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	build_token_in(int i, char *str, t_data *data)
{
	t_lexer	*tmp;

	tmp = NULL;
	if (str[i + 1] == '<')
	{
		tmp = ft_lexer_new(NULL, HERE_DOC, data->index);
		if (!tmp)
			ft_free(data, ERR_MALLOC, "Malloc_error", 2);
		ft_lexer_add_back(&data->lexer, tmp);
		i += 2;
	}
	else
	{
		tmp = ft_lexer_new(NULL, INFILE, data->index);
		if (!tmp)
			ft_free(data, ERR_MALLOC, "Malloc_error", 2);
		ft_lexer_add_back(&data->lexer, tmp);
		i++;
	}
	return (i);
}

static int	build_token_out(int i, char *str, t_data *data)
{
	t_lexer	*tmp;

	tmp = NULL;
	if (str[i + 1] == '>')
	{
		tmp = ft_lexer_new(NULL, OUTFILE_APPEND, data->index);
		if (!tmp)
			ft_free(data, ERR_MALLOC, "Malloc_error", 2);
		ft_lexer_add_back(&data->lexer, tmp);
		i += 2;
	}
	else
	{
		tmp = ft_lexer_new(NULL, OUTFILE, data->index);
		if (!tmp)
			ft_free(data, ERR_MALLOC, "Malloc_error", 2);
		ft_lexer_add_back(&data->lexer, tmp);
		i++;
	}
	return (i);
}

int	build_token(int i, char *str, t_data *data)
{
	t_lexer	*tmp;

	tmp = NULL;
	if (str[i] == '|')
	{
		tmp = ft_lexer_new(NULL, PIPE, data->index);
		if (!tmp)
			ft_free(data, ERR_MALLOC, "Malloc_error", 2);
		ft_lexer_add_back(&data->lexer, tmp);
		i++;
	}
	else if (str[i] == '<')
		i = build_token_in(i, str, data);
	else if (str[i] == '>')
		i = build_token_out(i, str, data);
	return (i);
}
