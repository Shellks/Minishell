/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_quote_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 07:11:54 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/27 07:14:26 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_next_expand_quote(t_data *data, char *str, char *tmp2, int i)
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
		while (end->word[i] && end->word[i] != ' ')
			i++;
		start = i;
		while (end->word[i])
			i++;
		tmp2 = ft_strndup(&end->word[start], (i - start));
		tmp1 = ft_strjoin(tmp1, tmp2);
		end->word = tmp1;
		free(tmp2);
	}
}

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