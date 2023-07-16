/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_here_doc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:28:24 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/16 18:49:29 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *check_exclamation_expand(t_data *data, char *str, int *j)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strndup(str, *j);
	if (!tmp1)
		ft_free_exit(data, ERR_MALLOC, "Malloc_error\n");
	dprintf(2, "tmp1 = %s\n", tmp1);
	tmp2 = ft_strdup(&str[*j + 2]);
	if (!tmp2)
		free_exit_env(data, tmp1, NULL, 1);
	dprintf(2, "tmp2 = %s\n", tmp2);
	str = ft_strjoin(tmp1, tmp2);
	if (!str)
		free_exit_env(data, tmp1, tmp2, 2);
	free(tmp1);
	free(tmp2);
	j += 2;
	return (str);
}

static char	*check_backslah_quote_expand(t_data *data, char *str, int *i)
{
	if (str[*i] == '\\' && str[*i + 1] && str[*i + 1] == '$')
	{
		str = ft_strdup(&str[*i + 2]);
		if (!str)
			ft_free_exit(data, ERR_MALLOC, "Malloc_error\n");
		*i += 1;
	}
	else
		*i += 2;
	dprintf(2, "strprout = %s\n", &str[*i]);
	return (str);
}

static char	*replace_false_heredoc_expand(t_data *data, char *str, int *j)
{
	char	*tmp1;
	char	*tmp2;

		dprintf(2, "str_old = %s\n", str);
		tmp1 = ft_strndup(str, *j);
		if (!tmp1)
			ft_free_exit(data, ERR_MALLOC, "Malloc_error\n");
		dprintf(2, "tmp1 = %s\n", tmp1);
		while (str[*j] && isalnum(str[*j]))
			j++;
		tmp2 = ft_strdup(&str[*j]);
		if (!tmp2)
			free_exit_env(data, tmp1, NULL, 1);
		dprintf(2, "tmp2 = %s\n", tmp2);
		free(str);
		str = ft_strjoin(tmp1, tmp2);
		if (!str)
			free_exit_env(data, tmp1, tmp2, 2);
		dprintf(2, "str_new = %s\n", str);
		free(tmp1);
		free(tmp2);
	return (str);
}

static char	*create_expand_here_doc(t_data *data, t_env *env, char *str, int *j)
{
	char	*tmp1;
	char	*tmp2;
	int		i;
	
	i = *j;
	// while (to_find[i] && isalnum(to_find[i]))
	// 	i++;
	dprintf(2, "str de join %s \n", &str[*j]);
	tmp1 = ft_strndup(str, *j);
	if (!tmp1)
		ft_free_exit(data, ERR_MALLOC, "Malloc_error\n");
	tmp2 = ft_strjoin(tmp1, env->content);
	if (!tmp2)
		free_exit_env(data, tmp1, NULL, 1);
	free(tmp1);
	i++;
	while (str[i] && isalnum(str[i]))
		i++;
	tmp1 = ft_strdup(&str[i]);
	if (!tmp1)
		free_exit_env(data, tmp2, NULL, 1);
	free(str);
	str = ft_strjoin(tmp2, tmp1);
	if (!str)
		free_exit_env(data, tmp1, tmp2, 2);
	*j += ft_strlen(env->content);
	dprintf(2, "j = %d\n", *j);
	free(tmp1);
	free(tmp2);
	return (str);
}

static bool	check_expand_here_doc(t_data *data, t_env *env, char *to_find)
{
	int	i;

	(void)data;
	i = 0;
	while (to_find[i] && isalnum(to_find[i]))
		i++;
	if ((int)ft_strlen(env->name) < i)
	{
		if (ft_strncmp(to_find, env->name, i) == 0)
			return (true);
	}
	else
	{
		if (ft_strncmp(to_find, env->name, ft_strlen(env->name)) == 0)
			return (true);
	}
	return (false);
}

static char	*get_expand_here_doc(t_data *data, char *str, char *to_find, int *j)
{
	t_env	*env;

	env = data->env;
	while (env)
	{
		if (check_expand_here_doc(data, env, to_find) == true)
		{
			str = create_expand_here_doc(data, env, str, j);
			break ;
		}
		env = env->next;
	}
	if (env == NULL)
		str = replace_false_heredoc_expand(data, str, j);
	return (str);
}

//essayer de faire une nouvelle expand plus propre en itérant tout str sur une seconde chaine expand par expand
//ca devrait gerer tout les problemes, meme les suites de $$ inchallah
char   *expand_here_doc(t_data *data, char *str)
{
	int	j;

	j = 0;
	while(str[j])
	{
		while (str[j] && str[j] != '$')
			j++;
		while (str[j] && str[j + 1] && str[j + 1] == '$')
			j++;
		if (!str[j] || !str[j + 1])
			break ;
		if (str[j + 1] == '!')
			str = check_exclamation_expand(data, str, &j);
		else if (str[j + 1] == '?')
			expand_status(data, &str[j + 1]);
		else if (ft_isdigit(str[1]) == 1)
			create_expand_digit(data, &str[j + 1]);
		else if (str[j + 1] == '\\' || (str[j] == '\\' && str[j + 1] == '$'))
			str = check_backslah_quote_expand(data, str, &j);
		else if (str[j + 1] != '\0' && str[j + 1] != '?' && \
		ft_isdigit(str[j + 1]) != 1 && ft_isalpha(str[j + 1]))
			str = get_expand_here_doc(data, str, &str[j + 1], &j);
	}
	return (str);
}

// char   *expand_here_doc(t_data *data, char *str)
// {
// 	char	*tmp1;
// 	char	*tmp2;
// 	int	j;

// 	j = 0;
// 	while(str[j])
// 	{
// 		dprintf(2, "&str[%d] = %s\n", j, &str[j]);
// 		while (str[j] && str[j] != '$')
// 			j++;
// 		while (str[j] && str[j + 1] && str[j + 1] == '$')
// 			j++;
// 		if (!str[j] || !str[j + 1])
// 			break ;
// 		if (str[j + 1] == '!')
// 			str = check_exclamation_expand(data, str, &j);
// 		else if (str[j + 1] == '?')
// 			expand_status(data, &str[j + 1]);
// 		else if (ft_isdigit(str[1]) == 1)
// 			create_expand_digit(data, &str[j + 1]);
// 		else if (str[j + 1] == '\\' || (str[j] == '\\' && str[j + 1] == '$'))
// 			str = check_backslah_quote_expand(data, str, &j);
// 		else if (str[j + 1] != '\0' && str[j + 1] != '?' && 
// 		ft_isdigit(str[j + 1]) != 1 && ft_isalpha(str[j + 1]))
// 		{
// 			dprintf(2, "strlol [%d] = %s\n", j, &str[j]);
// 			str = get_expand_here_doc(data, str, &str[j + 1], &j);
// 		}
// 	}
// 	return (str);
// }

// char   *expand_here_doc(t_data *data, char *str, int i)
// {
// 	int		j;

// 	j = 0;
// 	(void)i;
// 	while (str[j])
// 	{
// 		//dprintf(2, "str = %s\n", str);
// 		if (find_dollar(&str[j]) == true)
// 			while (str[j] == '$' && str[j + 1] == '$')
// 				j++;
// 			// if (str[j] == '$' && str[j + 1] == '$')
// 			// 	str = rm_dollar_expand_heredoc(data, str);
// 		if (str[j] == '$' && !str[j + 1])
// 			break ;
// 		if (str[j] == '$' && str[j + 1] == '!')
// 			str = check_exclamation_expand(data, str, &j);
// 		else if ((str[j] == '$' && str[j + 1] == '\\') || (str[j] == '\\' && str[j + 1] == '$'))
// 			str = check_backslah_quote_expand(data, str, &j);
// 		else if (str[j] == '$' && str[j + 1] != '\0' && 
// 		str[j + 1] != '?' && ft_isdigit(str[j + 1]) != 1 && ft_isalpha(str[j + 1]))
// 		{
// 			dprintf(2, "strlol [%d] = %s\n", j, &str[j]);
// 			str = get_expand_here_doc(data, str, &str[j + 1], &j);
// 		}
// 		else if (str[j] == '$' && str[j + 1] == '?')
// 			expand_status(data, &str[j + 1]);
// 		else if (str[j] == '$' && ft_isdigit(str[1]) == 1)
// 			create_expand_digit(data, &str[j + 1]);
// 		//dprintf(2, "str[j] = %s\n", &str[j]);
// 		if (str[j] == '$' && str[j + 1] == ' ')
// 			j++;
// 		while (str[j] && str[j] != '$')
// 		{
// 			//dprintf(2, "str = %c\n", str[j]);
// 			j++;
// 		}
// 	}
// 	return (str);
// }

// char	*rm_dollar_expand_heredoc(t_data *data, char *str)
// {
// 	char	*tmp1;
// 	char	*tmp2;
// 	int		i;

// 	i = 0;	
// 	while (str[i] && str[i] != '$' && str[i + 1] != '$')
// 		i++;
// 	if (str[i] && str[i] != '$')
// 		i++;
// 	tmp1 = ft_strndup(str, i);
// 	if (!tmp1)
// 		ft_free_exit(data, ERR_MALLOC, "Malloc_error\n");
// 	while (str[i] == '$' && str[i + 1] == '$')
// 		i++;
// 	printf("str de i = %s\n", &str[i]);
// 	tmp2 = ft_strdup(&str[i]);
// 	if (!tmp2)
// 		free_exit_env(data, tmp1, NULL, 1);
// 	free(str);
// 	str = ft_strjoin(tmp1, tmp2);
// 	if (!str)
// 		free_exit_env(data, tmp1, tmp2, 2);
// 	return (str);
// }