/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_in_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:02:56 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/26 23:38:02 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	create_expand_quote(t_data *data, t_env *env, char *str)
{
	char	*tmp1;
	char	*tmp2;
	int		start;
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
	if (str[i++])
	{
		while (str[i] && str[i] != '$' && str[i] != ' ')
			i++;
		start = i;
		while (str[i])
			i++;
	//	printf("str[start] = |%s|\n", &str[start]);
		tmp1 = ft_strndup(&str[start], (i - start));
		tmp2 = ft_strjoin(tmp2, tmp1);
		if (!tmp2)
			ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
	}
	ft_lexer_last(data->lexer)->word = tmp2;
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
	char	*tmp1;
	char	*tmp2;
	int		i;
	int		start;

	env = data->env;
	i = 0;
	end = ft_lexer_last(data->lexer);
	while (env)
	{
		if (check_expand_quote(env, str) == true)
		{
		//	printf("THE OLD STR = |%s|\n", cur->word);
			create_expand_quote(data, env, end->word);
		}
		// else
		// {
		printf("End->word = %s\n", end->word);
			if (env->next == NULL)
			{
				while (end->word[i] && end->word[i] != '$')
					i++;
				if (end->word[i] == '$')
				{
					tmp1 = ft_strndup(end->word, i);
					printf("tmp1 = |%s|\n", tmp1);
					while (end->word[i] && end->word[i] != ' ')
						i++;
					if (!end->word[i])
					{
						start = i;
						while (end->word[i])
							i++;
						tmp2 = ft_strndup(&end->word[start], (i - start));
						printf("tmp2 = |%s|\n", tmp1);
						tmp1 = ft_strjoin(tmp1, tmp2);
						end->word = tmp1;
						free(tmp2);
					}
				}
			}
		env = env->next;
		}
	//	printf("Env->word : |%s|\n", end->word);
}

void	expand_in_quote(t_data *data, char *str)
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
				get_expand_quote(data, &str[i + 1]);
			printf("str[%d] = %c\n", i, str[i]);
			i++;
		}
	}
}
