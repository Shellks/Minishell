/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:38:43 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/07 10:49:02 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_expand_status(t_data *data, char *str)
{
	char	*tmp;
	char	*err_code;

	err_code = ft_itoa(g_status);
	if (!err_code)
		ft_free(data, ERR_MALLOC, "Malloc_error", 2);
	tmp = ft_strjoin(err_code, str);
	if (!tmp)
	{
		ft_free(data, ERR_MALLOC, "Malloc_error", 2);
		free(err_code);
	}
	free(err_code);
	free(str);
	return (tmp);
}

void	expand_status(t_data *data, char *str)
{
    t_lexer *tmp_lexer;
	char	*tmp;
	int		start;
	int		i;

	i = 0;
	if (str[i] == '?')
		i++;
	start = i;
	while (str[i])
		i++;
	tmp = ft_strndup(&str[start], i);
	if (!tmp)
		ft_free(data, ERR_MALLOC, "Malloc_error", 2);
	tmp = get_expand_status(data, tmp);
    tmp_lexer = ft_lexer_last(data->lexer);
	if (tmp_lexer->word)
		free(tmp_lexer->word);
	tmp_lexer->word = tmp;
}
