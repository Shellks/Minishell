/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:19:18 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/24 13:32:06 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**bubble_sort_tab(char **tab, int len)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (tab[i] && i < len)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(tab[j], tab[j + 1]) > 0)
			{
					tmp = tab[j];
					tab[j] = tab[j + 1];
					tab[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (tab);
}

static char	*get_content_tab(t_data *data, t_env *env, char	*str)
{
	char	*tmp;

	tmp = str;
	str = ft_strjoin(tmp, "\"");
	if (!str)
		free_exit_env(data, tmp, NULL, 1);
	free (tmp);
	tmp = str;
	if (env->content != NULL)
	{
		str = ft_strjoin(tmp, env->content);
		if (!str)
			free_exit_env(data, tmp, NULL, 1);
		free (tmp);
		tmp = str;
	}
	str = ft_strjoin(tmp, "\"");
	if (!str)
		free_exit_env(data, tmp, NULL, 1);
	free (tmp);
	return (str);
}

static char	*get_string_tab_export(t_data *data, t_env *env)
{
	char	*str;

	if (env->equals == EQUALS)
	{
		str = ft_strjoin(env->name, "=");
		if (!str)
			ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
		str = get_content_tab(data, env, str);
	}
	else
	{
		str = ft_strdup(env->name);
		if (!str)
			ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
	}
	return (str);
}

char	**get_env_tab_sort(t_data *data)
{
	t_env	*tmp_env;
	char	**tab;
	int		len;

	tmp_env = data->env;
	len = ft_env_size(tmp_env);
	tab = (char **)ft_calloc(sizeof(char *), len + 1);
	if (!tab)
		ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
	len = 0;
	while (tmp_env)
	{
		tab[len] = get_string_tab_export(data, tmp_env);
		tmp_env = tmp_env->next;
		len++;
	}
	len = 0;
	while (tab[len])
		len++;
	tab = bubble_sort_tab(tab, len);
	return (tab);
}

void	ft_export_no_args(t_data *data)
{
	char	**tab;
	int		i;

	tab = get_env_tab_sort(data);
	i = -1;
	while (tab[++i])
	{
		if (tab[i][0] == '_' && (tab[i][1] == '=' || !tab[i][1]))
		{
			if (tab[i + 1])
				continue ;
			else
				break ; 
		}
		printf("declare -x %s\n", tab[i]);
	}
	ft_free_split(tab);
}
