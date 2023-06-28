/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:07:51 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/28 18:37:57 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	manage_space_quote(t_data *data, t_env *env, int *start)
// {
// 	t_lexer	*new;
// 	int		i;

// 	i = *start;
// 	while (env->content[i] && env->content[i] == ' ')
// 		i++;
// 	if (!env->content[i])
// 		return (FALSE);
// 	else
// 	{
// //		printf("Start in space : %d\n", *start);
// 		if (*start != 0 && env->content[*start] == ' ')
// 		{
// 			new = ft_lexer_new(NULL, DELIMITER, data->index);
// 			if (!new)
// 				ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
// 			ft_lexer_add_back(&data->lexer, new);
// 			data->index++;
// 			return (TRUE);
// 		}
// 	}
// 	return(-1);
// }

// static char	*get_word_quote(t_data *data, t_env *env, int *start)
// {
// 	char	*tmp;
// 	int		j;
// 	int		i;
// 	int		end;

// 	end = 0;
// 	j = 0;
// 	i = *start;
// 	// printf("Test : start : %d\n", *start);
// 	// printf("env-content : %c\n", env->content[i]);
// 	while (env->content[*start] && env->content[*start] != ' ')
// 		*start += 1;
// //	printf("len of path : %ld\n", ft_strlen(env->content));
// 	if (!env->content)
// 		return (NULL);
// 	end = *start - i;
// 	tmp = (char *)ft_calloc(sizeof(char), end + 1);
// 	if (!tmp)
// 		ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
// 	// *start += ft_strlcpy(tmp, env->content, (end + 1));
// 	while(env->content[i] && j < end)
// 	{
// 		tmp[j] = env->content[i];
// 	//	printf("tmp[%d] = %c\n", i, tmp[i]);
// 		i++;
// 		j++;
// 	}
// 	tmp[j] = '\0';
// 	return (tmp);
// }

// bool	check_env_expand(t_data *data, t_env *env, char *str)
// {
// 	t_lexer	*new;
// 	char	*tmp;
// 	int		start;

// 	(void)str;
// 	start = 0;
// 	while(env->content[start])
// 	{
// 		if (manage_space_quote(data, env, &start) == FALSE)
// 			break ;
// 		while (env->content[start] && env->content[start] == ' ')
// 			start++;
// 		tmp = get_word_quote(data, env, &start);
// 		if (!tmp)
// 			return (false);
// 		new = ft_lexer_new(tmp, WORD, data->index);
// 		if(!new)
// 			ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
// 		ft_lexer_add_back(&data->lexer, new);
// 		data->index++;
// 		start++;
// 	}
// 	return (true);
// }

void	create_expand_digit(t_data *data, char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (i == 1)
	{
		tmp = ft_strdup("");
		if (!tmp)
			ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
	}
	else
	{
		str++;
		tmp = ft_strndup(str, i - 1);
		if (!tmp)
			ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
	}
	ft_lexer_last(data->lexer)->word = tmp;
}

int	get_word(t_data *data, char *str, int start, int stop)
{
	t_lexer	*new;
	int		i;
	char	*tmp;

	i = start;
	tmp = NULL;
	i++;
	while(str[i] && str[i] != '$' && str[i] != ' ' && i < stop)
		i++;
	i -= start;
	tmp = ft_strndup(&str[start], i);
	new = ft_lexer_new(tmp, WORD, data->index);
	if (!new)
		ft_free(data, ERR_MALLOC, "Malloc_error\n", 1);
	ft_lexer_add_back(&data->lexer, new);
	i += start;
	return (i);
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
