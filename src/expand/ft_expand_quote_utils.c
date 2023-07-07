/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_quote_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 07:11:54 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/07 23:40:05 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*next_expand_word(t_data *data, char *str, char *tmp2, int i)
{
	int		start;
	char	*tmp1;
	char	*final_tmp;

	start = i;
	while (str[i])
		i++;
	tmp1 = ft_strndup(&str[start], (i - start));
	if (!tmp1)
		free_exit_env(data, tmp2, NULL, 1);
	final_tmp = ft_strjoin(tmp2, tmp1);
	if (!final_tmp)
		free_exit_env(data, tmp1, tmp2, 2);
	free(tmp1);
	free(tmp2);
	return (final_tmp);
}

void	get_next_expand(t_data *data, char *str, char *tmp2, int i)
{
	t_lexer	*tmp_lexer;
	char	*tmp;

	i++;
	while (str[i] && str[i] != '$' && str[i] != ' ')
		i++;
	tmp = next_expand_word(data, str, tmp2, i);
	tmp_lexer = ft_lexer_last(data->lexer);
	if (tmp_lexer->word)
		free(tmp_lexer->word);
	tmp_lexer->word = tmp;
}

static char	*rm_false_expand_word(t_data *data, t_lexer *end, int *start, int *i)
{
	char	*final_tmp;
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strndup(end->word, *i);
	if (!tmp1)
		ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
	*i += 1;
	while (end->word[*i] && end->word[*i] != ' ' && end->word[*i] != '$')
		*i += 1;
	*start = *i;
	while (end->word[*i])
		*i += 1;
	tmp2 = ft_strndup(&end->word[*start], (*i - *start));
	if (!tmp2)
		free_exit_env(data, tmp1, NULL, 1);
	final_tmp = ft_strjoin(tmp1, tmp2);
	if (!final_tmp)
		free_exit_env(data, tmp1, tmp2, 2);
	free(tmp1);
	free(tmp2);
	return (final_tmp);
}

void	replace_false_expand_quote(t_data *data, t_lexer *end)
{
	char	*tmp;
	int		i;
	int		start;

	i = 0;
	while (end->word[i] && end->word[i] != '$')
			i++;
	if (end->word[i] == '$')
	{
		tmp = rm_false_expand_word(data, end, &start, &i);
		if (end->word)
			free(end->word);
		end->word = tmp;
	}
}

int	get_word_in_quote(t_data *data, char *str, int start, int stop)
{
	t_lexer	*new;
	int		i;
	char	*tmp;

	i = start;
	tmp = NULL;
	if (check_backslah_quote(data, str, &i) == true)
		return (i);
	while (str[i] && str[i] != '=' && str[i] != '$' && str[i] != ' ' \
	&& str[i] != 28 && str[i] != '\\' &&i < stop)
		i++;
	i -= start;
	tmp = ft_strndup(&str[start], i);
	if (!tmp)
		ft_free_exit(data, ERR_MALLOC, "Malloc_error\n");
	new = ft_lexer_new(tmp, WORD);
	if (!new)
	{
		free(tmp);
		ft_free_exit(data, ERR_MALLOC, "Malloc_error\n");
	}
	ft_lexer_add_back(&data->lexer, new);
	return (i += start);
}
