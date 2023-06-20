/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:11:26 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/20 13:19:01 by nibernar         ###   ########.fr       */
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
	if (str[i] == ' ')
	{
		tmp = ft_lexer_new(NULL, DELIMITER, data->index);
		ft_lexer_add_back(&data->lexer, tmp);
		data->index++;
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
	// while(temp[j])
	// 	if (temp[j] == '$')
	// 		ft_expand(data, j);
	tmp = ft_lexer_new(temp, WORD, data->index);
	if (!tmp)
		ft_free(data, ERR_MALLOC, "Malloc error", 2);
	ft_lexer_add_back(&data->lexer, tmp);
	return (i + j);
}


// static int	build_cmd(int i, char *str, t_data *data)
// {
// 	int		j;
// 	t_lexer	*tmp;

// 	tmp = NULL;
// 	j = 0;
// 	while (str[i + j] && str[i + j] != ' ' && check_token(i + j, str) == false)
// 		j++;
// 	tmp = ft_lexer_new(ft_strndup(&str[i], j), 0, data->index);
// 	ft_lexer_add_back(&data->lexer, tmp);
// 	return (i + j);
// }

void	lexer(t_data *data)
{
	int	i;

	i = 0;
	data->index = 0;
	data->lexer = NULL;
	data->quote_error = 0;
	while (data->input[i] != '\0')
	{
		if (data->input[i] == 34 || data->input[i] == 39)
		{
			i = check_quote(data, i);
			if (data->quote_error == FALSE)
				return ;
		}
		if (data->input[i] == ' ')
			i = skipe_space(i, data->input, data);
		if (check_token(i, data->input) == true)
			i = build_token(i, data->input, data);
		else if (data->input[i] != ' ' && data->input[i] != 0)
			i = build_cmd(i, data->input, data);
		printf("%d\n", i);
		data->index++;
	}
	print_lexer(&data->lexer);
}
