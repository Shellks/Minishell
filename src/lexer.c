/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:11:26 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/26 20:27:23 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		tmp = ft_lexer_new(NULL, DELIMITER, data->index);
		ft_lexer_add_back(&data->lexer, tmp);
	}
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

static int	build_cmd(int i, char *str, t_data *data)
{
	int	j;
	t_lexer *tmp;
	char	*temp;

	j = 0;
	temp = NULL;
	while (str[i + j] && str[i + j] != ' ' && str[i + j] != 34 && str[i + j] != 39)
		j++;
	temp = ft_strndup(&str[i], j);
	tmp = ft_lexer_new(temp, WORD, data->index);
	if (!tmp)
		ft_free(data, ERR_MALLOC, "Malloc error", 2);
	ft_lexer_add_back(&data->lexer, tmp);
//	printf("i + j = %d\n", i + j);
	expand(data, temp);
	return (i + j);
}

void	lexer(t_data *data)
{
	int	i;

	i = 0;
	data->index = 0;
	data->lexer = NULL;
	data->quote_error = 0;
	while (data->input[i] != '\0')
	{
		if (data->input[i] == ' ')
			i = skipe_space(i, data->input, data);
		else if (data->input[i] == 34 || data->input[i] == 39)
		{
			i = check_quote(data, i);
			if (data->quote_error == FALSE)
			{
				printf("Syntax error : odd number of quotes\n");
				return ;
			}
		}
		else if (check_token(i, data->input) == true)
			i = build_token(i, data->input, data);
		else if (data->input[i] != ' ' && data->input[i] != 0)
			i = build_cmd(i, data->input, data);
//		printf("data->input[%d] : %c\n", i, data->input[1]);
		data->index++;
	}
	ft_fusion(data);
	print_lexer(&data->lexer);
}
