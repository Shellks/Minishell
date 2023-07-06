/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_quote_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 07:11:54 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/06 11:22:50 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_next_expand(t_data *data, char *str, char *tmp2, int i)
{
	char	*tmp1;
	int		start;

	i++;
	while (str[i] && str[i] != '$' && str[i] != ' ')
		i++;
	start = i;
	while (str[i])
		i++;
	tmp1 = ft_strndup(&str[start], (i - start));
	tmp2 = ft_strjoin(tmp2, tmp1);
	if (!tmp2)
		ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
	ft_lexer_last(data->lexer)->word = tmp2;
}

void	replace_false_expand_quote(t_lexer *end)
{
	char	*tmp1;
	char	*tmp2;
	int		i;
	int		start;

	i = 0;
	while (end->word[i] && end->word[i] != '$')
			i++;
	if (end->word[i] == '$')
	{
		tmp1 = ft_strndup(end->word, i);
		i++;
		while (end->word[i] && end->word[i] != ' ' && end->word[i] != '$')
			i++;
//		printf("end->word[i] = %s\n", &end->word[i]);
		start = i;
		while (end->word[i])
			i++;
		tmp2 = ft_strndup(&end->word[start], (i - start));
		tmp1 = ft_strjoin(tmp1, tmp2);
		end->word = tmp1;
		free(tmp2);
	}
}

int	get_word_in_quote(t_data *data, char *str, int start, int stop)
{
	t_lexer	*new;
	int		i;
	char	*tmp;

	i = start;
	tmp = NULL;
	if (str[i] == '\\' && str[i + 1] && str[i + 1] == '$')
	{
		tmp = ft_strndup(&str[i + 1], 1);
		new = ft_lexer_new(tmp, WORD, data->index);
		ft_lexer_add_back(&data->lexer, new);
		return (i + 2);
	}
	else
		i++;
	while(str[i] && str[i] != '=' && str[i] != '$' && str[i] != ' ' \
	&& str[i] != 28 && str[i] != '\\' &&i < stop)
		i++;
	i -= start;
	tmp = ft_strndup(&str[start], i);
	new = ft_lexer_new(tmp, WORD, data->index);
	if (!new)
		ft_free(data, ERR_MALLOC, "Malloc_error\n", 1);
	ft_lexer_add_back(&data->lexer, new);
	return (i += start);
}
