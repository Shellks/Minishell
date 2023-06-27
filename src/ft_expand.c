/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:19:39 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/27 15:01:42 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


static int	create_expand_env(t_data *data, t_env *env, char *str)
{
	char	*tmp1;
	char	*tmp2;
	int		start;
	int		i;

	i = 0;
	start = 0;
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
		tmp2 = ft_strjoin(tmp2, tmp1);
		if (!tmp2)
			ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
	}
	ft_lexer_last(data->lexer)->word = tmp2;
	return (i - start);
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


//revoir la boucle env
//$123$PATH  de temps em temps le prog repasse dans ft_isdigit car i =142 et str[i] = 3
//si je fait $PATH puis $134, PATH ne s'affiche plus
static void	get_expand(t_data *data, char *s1)
{
	t_lexer	*end;
	t_env	*env;
	char	*tmp;
	int		i;
	int		j;

	env = data->env;
	i = 0;
	j = 0;
	end = ft_lexer_last(data->lexer);
	while (env)
	{
		if (check_expand(data, env, s1) == true)
			j = create_expand_env(data, env, end->word);
		else
		{
			while (end->word[i] && end->word[i] != '$')
				i++;
			tmp = ft_strndup(end->word, i);
			end->word = tmp;
		}
		//dprintf(2, "str : %s  lex_word : %s  i : %d \n", &s1[j], end->word, j);
			env = env->next;
	}
}

static int	create_expand_digit(t_data *data, char *str)
{
	dprintf(2, "aff str %s  \n", str);
	char	*tmp;
	int		i;

	i = 0;
	// if (str[0] == '$')
	// 	str++;
	while (str[i] && str[i] != '$' && (ft_isdigit(str[i]) == 1))
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
	dprintf(2, "aff du code err %s   i: %d\n", tmp, i);
	ft_lexer_last(data->lexer)->word = tmp;
	return (i);
}




void	expand(t_data *data, char *str)
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
				get_expand(data, &str[i + 1]);
			else if (str[i] == '?')
			{
				dprintf(2, "aff du code err %s\n", &str[i]);
			}
			else if (ft_isdigit(str[i]) == 1)
			{
				i = create_expand_digit(data, &str[i]);
				dprintf(2, "iiii %d   \n", i);
			}
			i++;
		}
	}
}

