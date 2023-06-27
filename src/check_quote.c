/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:09:35 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/27 15:18:44 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	get_string_quote(t_data *data, int j, int len, char quote)
{
	t_lexer	*tmp;
	char	*str;
	int		i;
	
	tmp = NULL;
	i = -1;
	str = (char *)ft_calloc(sizeof(char), (len + 1));
	if (!str)
		ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
	j++;
//	printf("str[j] = %c\n", data->input[j]);
	while (data->input[j] && data->input[j] != quote && i <= len)
		str[++i] = data->input[j++];
	i++;
	str[i] = '\0';
	i = 0;
	tmp = ft_lexer_new(str, WORD, data->index);
	if (!tmp)
		ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
	ft_lexer_add_back(&data->lexer, tmp);
//	printf("STR == %s\n", str);
	if (quote == 34)
		expand_in_quote(data, str);
}

int	check_quote(t_data *data, int i)
{
	char	quote;
	int		j;

	quote = data->input[i];
	j = i;
	i++;
	while (data->input[i] && data->input[i] != quote)
	{
		i++;
	}
	if (data->input[i] == quote)
	{
		get_string_quote(data, j, (i - j), quote);
		return (i + 1);
	}
	else
		data->quote_error = 1;
	return (i + 1);
}
