/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:07:51 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/07 11:08:07 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_expand_digit(t_data *data, char *str)
{
	t_lexer	*tmp_lexer;
	char	*tmp;
	int		i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (i == 1)
	{
		tmp = ft_strdup("");
		if (!tmp)
			ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
	}
	else
	{
		str++;
		tmp = ft_strndup(str, i - 1);
		if (!tmp)
			ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
	}
	tmp_lexer = ft_lexer_last(data->lexer);
	if (tmp_lexer->word)
		free(tmp_lexer->word);
	tmp_lexer->word = tmp;
}

int	get_anti_slash(int i, char *str, t_data *data)
{
	t_lexer	*new;
	char	*tmp;

	if (!str[i + 1])
		return (ft_print_syntax_error("\\"), -1);
	tmp = ft_strndup(&str[i + 1], 1);
	new = ft_lexer_new(tmp, WORD, data->index);
	ft_lexer_add_back(&data->lexer, new);
	return (i + 2);
}

int	get_word(t_data *data, char *str, int start, int stop)
{
	t_lexer	*new;
	int		i;
	char	*tmp;

	i = start;
	tmp = NULL;
	i++;
	while(str[i] && str[i] != '=' && str[i] != '$' && str[i] != ' ' \
	&& str[i] != 28 && i < stop)
		i++;
	i -= start;
	tmp = ft_strndup(&str[start], i);
	if (!tmp)
		ft_free(data, ERR_MALLOC, "Malloc_error\n", 1);
	new = ft_lexer_new(tmp, WORD, data->index);
	if (!new)
		ft_free(data, ERR_MALLOC, "Malloc_error\n", 1);
	ft_lexer_add_back(&data->lexer, new);
	i += start;
	return (i);
}

bool	find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}
