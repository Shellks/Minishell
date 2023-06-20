/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:09:35 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/20 13:18:50 by nibernar         ###   ########.fr       */
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
	// while (data->input[j] && data->input[j] != '$')
	// 	if (data->input[j] == '$' && quote != 39)
	// 		ft_expand(data, j);
	tmp = ft_lexer_new(str, WORD, data->index);
	if (!tmp)
		ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
	ft_lexer_add_back(&data->lexer, tmp);
}

//boucle 
int	check_quote(t_data *data, int i)
{
	char	quote;
	int		j;

	quote = data->input[i];
	j = i;
	if (i > 1)
		i++;
	while (data->input[i] && data->input[i] != quote)
	{
		i++;
	}
	if (data->input[i] == quote)
	{
		get_string_quote(data, j, quote);
		return (i + j);
	}
	if (!data->input[i])
		return(printf("Syntax error\n"), FALSE);
	printf("Test\n");
	data->quote_error = 1;
	return (i + j + 1);
}
