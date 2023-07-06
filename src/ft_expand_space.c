/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:19:03 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/06 11:59:48 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

//STOOOOOOOOOOOOOOOOOOOOOOOOOP!!!!!!!

#include "../include/minishell.h"

static void manage_end_space(t_data *data, t_env *env, int *i, int *start)
{
    t_lexer *new;

    if (*start == 0)
			return ;
	if (env->content[*i - 1] == ' ')
	{
		new = ft_lexer_new(NULL, DELIMITER, data->index);
		if (!new)
			ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
		ft_lexer_add_back(&data->lexer, new);
		data->index++;
		*start += *i;
	}
}

static int	manage_space_quote(t_data *data, t_env *env, int *start)
{
	t_lexer	*new;
	int		i;

	i = *start;
	while (env->content[i] && env->content[i] == ' ')
		i++;
	if (!env->content[i])
	{
        manage_end_space(data, env, &i, start);
		return (FALSE);
	}
	else
	{
		if (env->content[*start] == ' ')
		{
			new = ft_lexer_new(NULL, DELIMITER, data->index);
			if (!new)
				ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
			ft_lexer_add_back(&data->lexer, new);
			data->index++;
			return (TRUE);
		}
	}
	return(-1);
}

static char	*get_word_quote(t_data *data, t_env *env, int *start)
{
	char	*tmp;
	int		j;
	int		i;
	int		end;

	end = 0;
	j = 0;
	i = *start;
	while (env->content[*start] && env->content[*start] != ' ')
		*start += 1;
	if (!env->content[*start] && env->content[*start - 1] == ' ')
		return (NULL);
	end = *start - i;
	*start -= 1;
	tmp = (char *)ft_calloc(sizeof(char), end + 1);
	if (!tmp)
		ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
	while(env->content[i] && j < end)
	{
		tmp[j] = env->content[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	check_env_expand(t_data *data, t_env *env)
{
	t_lexer	*new;
	char	*tmp;
	int		start;

	start = 0;
	while(env->content[start])
	{
		if (manage_space_quote(data, env, &start) == FALSE)
			return ;
		while (env->content[start] && env->content[start] == ' ')
			start++;
		tmp = get_word_quote(data, env, &start);
		if (!tmp)
			return ;
		new = ft_lexer_new(tmp, WORD, data->index);
		if(!new)
			ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
		ft_lexer_add_back(&data->lexer, new);
		data->index++;
		start++;
	}
}
