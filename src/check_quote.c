/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:09:35 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/22 12:27:12 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	get_string_quote(t_data *data, int j, char quote)
{
	t_lexer	*tmp;
	char	*str;
	int		i;
	
	tmp = NULL;
	i = 0;
	str = (char *)ft_calloc(sizeof(char), ft_strlen(&data->input[j] + 1));
	if (!str)
		ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
	j++;
	while (data->input[j] && data->input[j] != quote)
		str[i++] = data->input[j++];
	i = 0;
	printf("str : %s\n", str);
	tmp = ft_lexer_new(str, WORD, data->index);
	if (!tmp)
		ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
	ft_lexer_add_back(&data->lexer, tmp);
	expand_in_quote(data, str);
}

//boucle 
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
		get_string_quote(data, j, quote);
		return (i + 1);
	}
	else
		data->quote_error = 1;
//	printf("le dernier input : %c\n", data->input[i]);
	return (i + 1);
}
