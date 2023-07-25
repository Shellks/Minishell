/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:09:35 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/25 12:49:38 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	get_string_quote(t_data *data, int j, int len, char quote)
{
	t_lexer	*tmp;
	char	*str;
	int		i;

	tmp = NULL;
	i = -1;
	str = (char *)ft_calloc(sizeof(char), (len + 1));
	if (!str)
		ft_free_exit(data, ERR_MALLOC, "Malloc_error\n");
	j++;
	while (data->input[j] && data->input[j] != quote && i <= len)
		str[++i] = data->input[j++];
	i++;
	str[i] = '\0';
	i = 0;
	tmp = ft_lexer_new(str, WORD, SINGLE);
	if (!tmp)
	{
		free(str);
		ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
	}
	ft_lexer_add_back(&data->lexer, tmp);
}

int	check_quote(t_data *data, int i)
{
	char	quote;
	int		j;
	int		check_quote;

	check_quote = 0;
	quote = data->input[i];
	j = (i + 1);
	i++;
	while (data->input[i] && data->input[i] != quote)
		i++;
	if (data->input[i] == quote && quote == 34)
	{
		check_quote = expand_in_quote(data, &data->input[j], (i - j));
		if (check_quote == 0)
			get_string_quote(data, (j - 1), (i - j), quote);
		return (i + 1);
	}
	else if (data->input[i] == quote && quote == 39)
		get_string_quote(data, (j - 1), (i - j), quote);
	else
		data->quote_error = 1;
	return (i + 1);
}
