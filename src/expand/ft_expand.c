/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:19:39 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/07 21:48:28 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


static void	create_expand(t_data *data, t_env *env, char *str, t_lexer *src)
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
	if (check_space_env_content(data, env, src) == true)
		free(tmp1);
	else
	{
		tmp2 = ft_strjoin(tmp1, env->content);
		if (!tmp2)
		{
			free(tmp1);
			ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
		}
		free(tmp1);
		get_next_expand(data, str, tmp2, i);
	}
}

static bool	check_expand(t_data *data, t_env *env, char *s1)
{
	int	i;

	(void)data;
	i = 0;
	while(s1[i] != '$' && s1[i] != '\0')
		i++;
	if ((int)ft_strlen(env->name) < i)
	{
		if (ft_strncmp(s1, env->name, i) == 0)
			return (true);
	}
	else
	{
		if (ft_strncmp(s1, env->name, ft_strlen(env->name)) == 0)
			return (true);
	}
	return (false);
}

static void	get_expand(t_data *data, char *str, t_lexer *src)
{
	t_lexer	*end;
	t_env	*env;

	env = data->env;
	end = ft_lexer_last(data->lexer);
	while (env)
	{
		if (check_expand(data, env, str) == true)
		{
			create_expand(data, env, end->word, src);
			break ;
		}
		env = env->next;
	}
	if (env == NULL)
		replace_false_expand_quote(data, end);
}

int		expand(t_data *data, char *str, int i)
{
	t_lexer		*cur;
	int		j;

	j = 0;
	while (str[j] && j < i)
	{
		if (find_dollar(&str[j]) == true)
			while (str[j] == '$' && str[j + 1] == '$')
				j++;
		j = get_word(data, str, j, i);
		cur = ft_lexer_last(data->lexer);
		// if (!cur || !cur->word)
		// 	break ;
		if (cur->word[0] == '$' && cur->word[1] != '\0' && \
		cur->word[1] != '?' && ft_isdigit(cur->word[1]) != 1)
			{
				get_expand(data, &cur->word[1], cur);
				cur = ft_lexer_last(data->lexer);
				// if (cur && cur->next)
				// 	cur = cur->next;
			}
		else if (cur->word[0] == '$' && cur->word[1] == '?')
			expand_status(data, &cur->word[1]);
		else if (cur->word[0] == '$' && ft_isdigit(cur->word[1]) == 1)
			create_expand_digit(data, &cur->word[1]);
	}
	return (j);
}
