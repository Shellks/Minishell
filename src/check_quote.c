/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:09:35 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/19 17:22:22 by acarlott         ###   ########lyon.fr   */
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
	printf("Test\n");
	while (data->input[j] && data->input[j] != quote)
		str[i++] = data->input[j++];
	printf("%s\n", str);
	i = 0;
	// while (data->input[j] && data->input[j] != '$')
	// 	if (data->input[j] == '$' && quote != 39)
	// 		ft_expand(data, j);
	tmp = ft_lexer_new(str, WORD, 0);
	if (!tmp)
		ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
	ft_lexer_add_back(&data->lexer, tmp);
}

int	check_quote(t_data *data, int i)
{
	char	quote;
	int		j;

	quote = data->input[i];
	j = i;
	i++;
	while (data->input[i] && data->input[i] != quote)
		i++;
	if (data->input[i] == quote)
	{
		get_string_quote(data, j, quote);
		return (i + j);
	}
	if (!data->input[i])
		return(printf("Syntax error\n"), FALSE);
	return (i);
}
