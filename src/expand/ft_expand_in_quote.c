/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_in_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:02:56 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/28 11:49:32 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	create_expand_quote(t_data *data, t_env *env, char *str)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	tmp1 = ft_strndup(str, i);
	if (!tmp1)
		ft_free_exit(data, ERR_MALLOC, "Malloc_error\n");
	if (env->content)
	{
		tmp2 = ft_strjoin(tmp1, env->content);
		if (!tmp2)
			free_exit_env(data, tmp1, NULL, 1);
		free(tmp1);
		if (str[i])
			get_next_expand(data, str, tmp2, i);
	}
	else
		if (str[i])
			get_next_expand(data, str, tmp1, i);
}

static bool	check_expand_quote(t_env *env, char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != '$' && str[i] != '\0')
		i++;
	if ((int)ft_strlen(env->name) < i)
	{
		if (ft_strncmp(str, env->name, i) == 0)
			return (true);
	}
	else
	{
		if (ft_strncmp(str, env->name, ft_strlen(env->name)) == 0)
			return (true);
	}
	return (false);
}

static void	get_expand_quote(t_data *data, char *str)
{
	t_lexer	*end;
	t_env	*env;

	env = data->env;
	end = ft_lexer_last(data->lexer);
	while (env)
	{
		if (check_expand_quote(env, str) == true)
		{
			create_expand_quote(data, env, end->word);
			break ;
		}
		env = env->next;
	}
	if (env == NULL)
		replace_false_expand_quote(data, end);
}

int	expand_in_quote(t_data *data, char *str, int i)
{
	t_lexer	*cur;
	int		j;

	j = 0;
	while (str[j] && j < i)
	{
		if (find_dollar(&str[j]) == true)
			while (str[j] == '$' && str[j + 1] == '$')
				j++;
		j = get_word_in_quote(data, str, j, i);
		cur = ft_lexer_last(data->lexer);
		if (cur->word[0] == '$' && cur->word[1] != '\0' \
			&& cur->word[1] != '?' && ft_isdigit(cur->word[1]) != 1)
			get_expand_quote(data, &cur->word[1]);
		if (cur->word[0] == '$' && cur->word[1] == '?')
			expand_status(data, &cur->word[1]);
		if (cur->word[0] == '$' && ft_isdigit(cur->word[1]) == 1)
			create_expand_digit(data, &cur->word[1]);
	}
	return (j);
}
