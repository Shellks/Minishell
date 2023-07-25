/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:07:51 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/25 17:43:13 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	check_backslah_quote(t_data *data, char *str, int *i)
{
	t_lexer	*new;
	char	*tmp;

	if (str[*i] == '\\' && str[*i + 1] && str[*i + 1] == '$')
	{
		tmp = ft_strndup(&str[*i + 1], 1);
		if (!tmp)
			ft_free_exit(data, ERR_MALLOC, "Malloc_error\n");
		new = ft_lexer_new(tmp, WORD, DOUBLE);
		if (!new)
		{
			free(tmp);
			ft_free_exit(data, ERR_MALLOC, "Malloc_error\n");
		}
		ft_lexer_add_back(&data->lexer, new);
		*i += 2;
		return (true);
	}
	else
	{
		*i += 1;
		return (false);
	}
}

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
			ft_free_exit(data, ERR_MALLOC, "Malloc_error\n");
	}
	else
	{
		str++;
		tmp = ft_strndup(str, i - 1);
		if (!tmp)
			ft_free_exit(data, ERR_MALLOC, "Malloc_error\n");
	}
	tmp_lexer = ft_lexer_last(data->lexer);
	if (tmp_lexer->word)
		free(tmp_lexer->word);
	tmp_lexer->word = tmp;
}

int	get_word(t_data *data, char *str, int start, int stop)
{
	t_lexer	*new;
	int		i;
	char	*tmp;

	i = start;
	tmp = NULL;
	i++;
	while (str[i] && str[i] != '=' && str[i] != '$' && str[i] != ' ' \
			&& str[i] != 28 && i < stop && ft_isalnum_modif(str[i]))
	{
		if ((i - 1) != start && str[i] == '?')
			break ;
		i++;
	}
	i -= start;
	tmp = ft_strndup(&str[start], i);
	if (!tmp)
		ft_free_exit(data, ERR_MALLOC, "Malloc_error\n");
	new = ft_lexer_new(tmp, WORD, NONE);
	if (!new)
	{
		free(tmp);
		ft_free_exit(data, ERR_MALLOC, "Malloc_error\n");
	}
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
