/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_in_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:02:56 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/22 16:50:44 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	check_env_expand(t_data *data, t_env *env, char *str)
{
	int	i;
	int	j;
	int	start;
	int	end;
	char	*tmp1;
	char	*tmp2;

	i = 0;
	start = 0;
	end = 0;
	while(env->content[i])
	{
		while (env->content[i] == ' ')
			i++;
		while (env->content && env->content[i + j] != ' ')
			j++;
		end = j;
		printf("End : %d\n", end);
		tmp1 = (char *)malloc(sizeof(char) * end);
		if (!tmp1)
			return ;
		j = 0;
		while (j < (end - i))
		{
			tmp[j++] = env->content[i++];
		}
		if (env->content)
			start = i + j;
		while (env->content)
	}
}

static void	create_expand_quote(t_data *data, t_env *env, char *str)
{
	char	*tmp1;
	char	*tmp2;
	int		start;
	int		i;
//	printf("old_tmp = %s\n", str);
	i = 0;
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

static bool	check_expand_quote(t_data *data, t_env *env, char *s1)
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

static void	get_expand_quote(t_data *data, char *s1)
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
		if (check_expand_quote(data, env, s1) == true)
			create_expand_quote(data, env, end->word);
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

void	expand_in_quote(t_data *data, char *str)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	if (find_dollar(str) == true)
	{
		while (str[i])
		{
			while (str[i] == '$' && str[i + 1] == '$')
				i++;
			if (str[i] == '$' && str[i + 1] != '\0')
				get_expand_quote(data, &str[i + 1]);
			i++;
		}
	}
}
