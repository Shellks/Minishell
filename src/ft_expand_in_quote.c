/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_in_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:02:56 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/27 07:13:36 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	create_expand_quote(t_data *data, t_env *env, char *str)
{
	char	*tmp1;
	char	*tmp2;
//	int		start;
	int		i;

//	printf("old_tmp = |%s|\n", str);
	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	tmp1 = ft_strndup(str, i);
	if (!tmp1)
		ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
	tmp2 = ft_strjoin(tmp1, env->content);
	free(tmp1);
	if (str[i])
		get_next_expand_quote(data, str, tmp2, i);
//	printf("new_tmp = |%s|\n", data->lexer->word);
}

static bool	check_expand_quote(t_env *env, char *str)
{
	int	i;

	i = 0;
	while(str[i] != ' ' && str[i] != '$' && str[i] != '\0')
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
		printf("End->word = %s\n", end->word);
		env = env->next;
	}
	if (env == NULL)
		replace_false_expand_quote(end);
}

void	expand_in_quote(t_data *data, char *str)
{
	int		i;

	i = 0;
	if (find_dollar(str) == true)
	{
		while (str[i])
		{
			while (str[i] == '$' && str[i + 1] == '$')
				i++;
			if (str[i] == '$' && str[i + 1] != '\0')
				get_expand_quote(data, &str[i + 1]);
			printf("str[%d] = %c\n", i, str[i]);
			i++;
		}
	}
}
