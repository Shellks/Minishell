/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_here_doc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:28:24 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/17 22:08:07 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*replace_false_heredoc_expand(t_data *data, char *str, int *j)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = 0;
	tmp1 = ft_strndup(str, *j);
	if (!tmp1)
		ft_free_exit(data, ERR_MALLOC, "Malloc_error\n");
	if (str[*j + i] == '$')
		i++;
	while (str[*j + i] && isalnum(str[*j + i]))
		i++;
	tmp2 = ft_strdup(&str[*j + i]);
	if (!tmp2)
		free_exit_env(data, tmp1, NULL, 1);
	free(str);
	str = ft_strjoin(tmp1, tmp2);
	if (!str)
		free_exit_env(data, tmp1, tmp2, 2);
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

char   *expand_here_doc(t_data *data, char *str)
{
	int	j;

	j = 0;
	while(j < (int)ft_strlen(str) && str[j])
	{
		while (str[j] && str[j] != '$')
			j++;
		while (str[j] && str[j + 1] && str[j + 1] == '$')
			j++;
		if (!str[j] || !str[j + 1])
			break ;
		else if (str[j + 1] == '?')
			str = expand_status_heredoc(data, str, j);
		else if (ft_isdigit(str[j + 1]))
			str = expand_digit_heredoc(data, str, j);
		else
			str = get_expand_here_doc(data, str, &str[j + 1], &j);
	}
	return (str);
}
