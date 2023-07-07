/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:31:26 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/07 23:44:15 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	build_token_in(int i, char *str, t_data *data)
{
	t_lexer	*tmp;

	tmp = NULL;
	if (str[i + 1] == '<')
	{
		tmp = ft_lexer_new(NULL, HERE_DOC);
		if (!tmp)
			ft_free_exit(data, ERR_MALLOC, "Malloc_error");
		ft_lexer_add_back(&data->lexer, tmp);
		i += 2;
	}
	else
	{
		tmp = ft_lexer_new(NULL, INFILE);
		if (!tmp)
			ft_free_exit(data, ERR_MALLOC, "Malloc_error");
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
		tmp = ft_lexer_new(NULL, OUTFILE_APPEND);
		if (!tmp)
			ft_free_exit(data, ERR_MALLOC, "Malloc_error");
		ft_lexer_add_back(&data->lexer, tmp);
		i += 2;
	}
	else
	{
		tmp = ft_lexer_new(NULL, OUTFILE);
		if (!tmp)
			ft_free_exit(data, ERR_MALLOC, "Malloc_error");
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
		tmp = ft_lexer_new(NULL, PIPE);
		if (!tmp)
			ft_free_exit(data, ERR_MALLOC, "Malloc_error");
		ft_lexer_add_back(&data->lexer, tmp);
		i++;
	}
	else if (str[i] == '<')
		i = build_token_in(i, str, data);
	else if (str[i] == '>')
		i = build_token_out(i, str, data);
	return (i);
}
int	get_anti_slash(int i, char *str, t_data *data)
{
	t_lexer	*new;
	char	*tmp;

	if (!str[i + 1])
		return (ft_print_syntax_error("\\"), -1);
	tmp = ft_strndup(&str[i + 1], 1);
	if (!tmp)
		ft_free_exit(data, ERR_MALLOC, "Malloc error \n");
	new = ft_lexer_new(tmp, WORD);
	if (!new)
	{
		free(tmp);
		ft_free_exit(data, ERR_MALLOC, "Malloc error \n");
	}
	ft_lexer_add_back(&data->lexer, new);
	return (i + 2);
}
