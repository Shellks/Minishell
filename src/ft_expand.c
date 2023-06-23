/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:19:39 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/23 10:58:28 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	create_expand(t_data *data, t_env *env, char *str)
{
	char	*tmp1;
	char	*tmp2;
	int		start;
	int		i;
//	printf("old_tmp = %s\n", str);
	i = 0;
	(void)env;
	while (str[i] && str[i] != '$')
		i++;
	tmp1 = ft_strndup(str, i);
	if (!tmp1)
		ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
	tmp2 = ft_strjoin(tmp1, env->content);
	free(tmp1);
	if (str[i])
	{
		i++;
		while (str[i] && str[i] != '$')
			i++;
		start = i;
		while (str[i])
			i++;
		tmp1 = ft_strndup(&str[start], (i - start));
		printf("tmp1 = %s\n", tmp1);
		tmp2 = ft_strjoin(tmp2, tmp1);
		if (!tmp2)
			ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
	}
	ft_lexer_last(data->lexer)->word = tmp2;
//	printf("new_tmp = %s\n", data->lexer->word);
}

static bool	check_expand(t_data *data, t_env *env, char *s1)
{
	int	i;

	i = 0;
	while(s1[i] != '$' && s1[i] != '\0')
		i++;
	(void)data;
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

static void	get_expand(t_data *data, char *s1)
{
	t_lexer	*end;
	t_env	*env;
	char	*tmp;
	int		i;

	env = data->env;
	i = 0;
	end = ft_lexer_last(data->lexer);
	while (env)
	{
		if (check_expand(data, env, s1) == true)
			create_expand(data, env, end->word);
		else
		{
			while (end->word[i] && end->word[i] != '$')
				i++;
			tmp = ft_strndup(end->word, i);
			end->word = tmp;
		}
		env = env->next;
	}
}
// si num apres $ skip le num et aff le rest ex : $12345 = 2345


void	expand(t_data *data, char *str)
{
	int		i;
	// char	*tmp;

	// tmp = NULL;
	i = 0;
	if (find_dollar(str) == true)
	{
		while (str[i])
		{
			while (str[i] == '$' && str[i + 1] == '$')
				i++;
			if (str[i] == '$' && str[i + 1] != '\0')
				get_expand(data, &str[i + 1]);
			i++;
		}
	}
}
