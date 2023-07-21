/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:11:26 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/20 18:28:49 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	check_token(int i, char *str)
{
	if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		return (true);
	return (false);
}

static int	skipe_space(int i, char *str, t_data *data)
{
	t_lexer	*tmp;
	int		j;

	j = i;
	while (str[j] && str[j] == ' ')
	{
		j++;
	}
	if (str[j] == '\0')
		return (j);
	tmp = NULL;
	if (data->lexer == NULL)
		return (j);
	else
	{
		tmp = ft_lexer_new(NULL, DELIMITER, NONE);
		if (!tmp)
			ft_free_exit(data, ERR_MALLOC, "Malloc_error");
		ft_lexer_add_back(&data->lexer, tmp);
	}
	while (str[i] && str[i] == ' ')
	{
		i++;
	}
	return (i);
}

static int	build_cmd(int i, char *str, t_data *data)
{
	int	j;

	j = 0;
	while (str[i + j] && str[i + j] != ' ' && \
			str[i + j] != 34 && str[i + j] != 39 && \
			str[i] != '\\' && check_token((i + j), str) == false)
	{
		if (str[i + j] == '\\')
			break ;
		j++;
	}
	expand(data, &str[i], j);
	return (i + j);
}

int	lexer_loop(t_data *data, int *i)
{
	if (data->input[*i] == '\\')
		*i = get_anti_slash(*i, data->input, data);
	if (*i == -1)
		return (-1);
	if (data->input[*i] == ' ')
		*i = skipe_space(*i, data->input, data);
	else if (data->input[*i] == 34 || data->input[*i] == 39)
	{
		*i = check_quote(data, *i);
		if (data->quote_error == FALSE)
		{
			printf("minishell: parse error: quote unclosed\n");
			return (-1);
		}
	}
	else if (check_token(*i, data->input) == true)
		*i = build_token(*i, data->input, data);
	else if (data->input[*i] != ' ' && data->input[*i] != 0)
		*i = build_cmd(*i, data->input, data);
	return (*i);
}

bool	lexer(t_data *data)
{
	int	i;

	i = 0;
	data->lexer = NULL;
	data->quote_error = 0;
	while (data->input[i] != '\0')
	{
		i = lexer_loop(data, &i);
		if (i == -1)
			return (false);
	}
	return (true);
}
