/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:07:51 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/26 20:04:36 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	manage_space_quote(t_data *data, t_env *env, int *start)
{
	t_lexer	*new;
	int		i;

	i = *start;
	printf("env->content : |%s|\n", env->content);
	while (env->content[i] && env->content[i] == ' ')
		i++;
	if (!env->content[i])
		return (FALSE);
	else
	{
//		printf("Start in space : %d\n", *start);
		if (*start != 0 && env->content[*start] == ' ')
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
	// printf("Test : start : %d\n", *start);
	// printf("env-content : %c\n", env->content[i]);
	while (env->content[*start] && env->content[*start] != ' ')
		*start += 1;
//	printf("len of path : %ld\n", ft_strlen(env->content));
	if (!env->content[*start])
		return (NULL);
	printf("Test\n");
	end = *start - i;
	tmp = (char *)ft_calloc(sizeof(char), end + 1);
	if (!tmp)
		ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
	// *start += ft_strlcpy(tmp, env->content, (end + 1));
	while(env->content[i] && j < end)
	{
		tmp[j] = env->content[i];
	//	printf("tmp[%d] = %c\n", i, tmp[i]);
		i++;
		j++;
	}
	tmp[j] = '\0';
//	printf("New-Word : %s\n", tmp);
	return (tmp);
}

bool	check_env_expand(t_data *data, t_env *env, char *str)
{
	t_lexer	*new;
	char	*tmp;
	int		start;

	(void)str;
	start = 0;
	while(env->content[start])
	{
		if (manage_space_quote(data, env, &start) == FALSE)
			break ;
		while (env->content[start] && env->content[start] == ' ')
			start++;
		tmp = get_word_quote(data, env, &start);
		if (!tmp)
			return (false);
		new = ft_lexer_new(tmp, WORD, data->index);
		if(!new)
			ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
		ft_lexer_add_back(&data->lexer, new);
		data->index++;
		start++;
	}
	return (true);
}

bool	find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}
