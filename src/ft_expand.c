/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:19:39 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/27 18:42:14 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


// static int	create_expand(t_data *data, t_env *env, char *str)
// {
// 	char	*tmp1;
// 	char	*tmp2;
// 	int		i;
	
// 	printf("old_tmp = %s\n", str);
// 	i = 0;
// //	printf("str[i] = %c\n", str[i]);
// 	while (str[i] && str[i] != '$')
// 		i++;
// 	tmp1 = ft_strndup(str, i);
// 	if (!tmp1)
// 		ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
// 	printf("tmp1 = %s\n", tmp1);
// 	check_env_expand(data, env, &str[i]);
// 	tmp2 = ft_strjoin(tmp1, env->content);
// 	free(tmp1);
// 	if (str[i])
// 		get_next_expand(data, str, tmp2, i);
// 	printf("new_tmp = %s\n", data->lexer->word);
// 	return (ft_strlen(tmp2));
// }

// static bool	check_expand(t_data *data, t_env *env, char *s1)
// {
// 	int	i;

// 	(void)data;
// 	i = 0;
// 	while(s1[i] != '$' && s1[i] != '\0')
// 		i++;
// 	if ((int)ft_strlen(env->name) < i)
// 	{
// 		if (ft_strncmp(s1, env->name, i) == 0)
// 			return (true);
// 	}
// 	else
// 	{
// 		if (ft_strncmp(s1, env->name, ft_strlen(env->name)) == 0)
// 			return (true);
// 	}
// 	return (false);
// }


// //revoir la boucle env
// //$123$PATH  de temps em temps le prog repasse dans ft_isdigit car i =142 et str[i] = 3
// //si je fait $PATH puis $134, PATH ne s'affiche plus
// static int	get_expand(t_data *data, char *s1)
// {
// 	t_lexer	*end;
// 	t_env	*env;
// 	int		i;

// 	env = data->env;
// 	end = ft_lexer_last(data->lexer);
// 	i = 0;
// 	while (env)
// 	{
// 		if (check_expand(data, env, s1) == true)
// 		{
// 			i = create_expand(data, env, end->word);
// 			break ;
// 		}
// 		//dprintf(2, "str : %s  lex_word : %s  i : %d \n", &s1[j], end->word, j);
// 			env = env->next;
// 	}
// 	if (env == NULL)
// 		replace_false_expand_quote(end);
// 	return (i);
// }

// static int	create_expand_digit(t_data *data, char *str)
// {
// 	dprintf(2, "aff str %s  \n", str);
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	// if (str[0] == '$')
// 	// 	str++;
// 	while (str[i] && str[i] != '$' && (ft_isdigit(str[i]) == 1))
// 		i++;
// 	if (i == 1)
// 	{
// 		tmp = ft_strdup("");
// 		if (!tmp)
// 			ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
// 	}
// 	else
// 	{
// 		dprintf(2, "data-lexer-zord |%s|  \n", data->lexer->word);
// 		str++;
// 		tmp = ft_strndup(str, i - 1);
// 		tmp = ft_strjoin(ft_lexer_last(data->lexer)->word, tmp);
// 		if (!tmp)
// 			ft_free(data, ERR_MALLOC, "Malloc_error\n", 2);
// 	}
// 	dprintf(2, "aff du code err %s   i: %d\n", tmp, i);
// 	ft_lexer_last(data->lexer)->word = tmp;
// 	return (i);
// }

static int	get_word(t_data *data, char *str, int start)
{
	t_lexer	*new;
	int		i;
	char	*tmp;

	i = start;
	tmp = NULL;
	i++;
	while(str[i] && str[i] != '$')
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


void	expand(t_data *data, char *str, t_lexer **old)
{
	int		i;

	i = 0;
	while (str[i] && find_dollar(&str[i]) == true)
	{
		while (str[i] == '$' && str[i + 1] == '$')
		 	i++;
		 i = get_word(data, str, i);
		// while (str[i])
		// {
		// 	if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != '?' && ft_isdigit(str[i]) != 1)
		// 		i += get_expand(data, &str[i + 1]);
		// 	if (str[i] == '$' && str[i + 1] == '?')
		// 	{
		// 		dprintf(2, "aff du code err %s\n", &str[i]);
		// 		i++;
		// 	}
		// 	if (str[i] == '$' && ft_isdigit(str[i + 1]) == 1)
		// 	{
		// 		i += create_expand_digit(data, &str[i + 1]);
		// 		dprintf(2, "iiii %d   \n", i);
		// 	}
		// 	i++;
		// 	dprintf(2, "caca%s   i : %d\n", &str[i], i);
		// }
		if (str[i] == '\0')
			ft_lexer_delone(&old);
	}
}

