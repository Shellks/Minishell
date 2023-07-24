/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:19:03 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/24 14:59:47 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	manage_end_space(t_data *data, t_env *env, int *i, int *start)
{
	t_lexer	*new;

	if (*start == 0)
		return (false);
	if (env->content[*i - 1] == ' ')
	{
		new = ft_lexer_new(NULL, DELIMITER, NONE);
		if (!new)
			ft_free_exit(data, ERR_MALLOC, "Malloc_error\n");
		ft_lexer_add_back(&data->lexer, new);
		*start += *i;
	}
	return (true);
}

static int	manage_space_content(t_data *data, t_env *env, int *start)
{
	t_lexer	*new;
	int		i;

	i = *start;
	while (env->content[i] && env->content[i] == ' ')
		i++;
	if (!env->content[i])
	{
		if (manage_end_space(data, env, &i, start) == false)
			return (-2);
		return (FALSE);
	}
	else
	{
		if (env->content[*start] == ' ')
		{
			new = ft_lexer_new(NULL, DELIMITER, NONE);
			if (!new)
				ft_free_exit(data, ERR_MALLOC, "Malloc_error\n");
			ft_lexer_add_back(&data->lexer, new);
			return (TRUE);
		}
	}
	return (-1);
}

static char	*get_word_in_content(t_data *data, t_env *env, int *start)
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
		ft_free_exit(data, ERR_MALLOC, "Malloc_error\n");
	while (env->content[i] && j < end)
	{
		tmp[j] = env->content[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

static int	space_env_loop(t_data *data, t_env *env, int *start, int *i)
{
	t_lexer	*new;
	char	*tmp;

	*i = manage_space_content(data, env, start);
	if (*i == FALSE)
		return (BREAK);
	if (*i == -2)
		return (FALSE);
	while (env->content[*start] && env->content[*start] == ' ')
		*start += 1;
	tmp = get_word_in_content(data, env, start);
	if (!tmp)
		return (BREAK);
	new = ft_lexer_new(tmp, WORD, NONE);
	if (!new)
	{
		free(tmp);
		ft_free_exit(data, ERR_MALLOC, "Malloc_error\n");
	}
	ft_lexer_add_back(&data->lexer, new);
	return (TRUE);
}

bool	check_space_env_content(t_data *data, t_env *env, t_lexer *src)
{
	int		check;
	int		start;
	int		i;

	i = 0;
	start = 0;
	if (!env->content)
		return (false);
	while (env->content[start] && env->content[start] != ' ')
		start++;
	if (!env->content[start])
		return (false);
	start = -1;
	while (env->content[++start])
	{
		check = space_env_loop(data, env, &start, &i);
		if (check == BREAK)
			break ;
		else if (check == FALSE)
			return (false);
	}
	if (!src->previous)
		data->lexer = data->lexer->next;
	ft_lexer_delone(src);
	return (true);
}
