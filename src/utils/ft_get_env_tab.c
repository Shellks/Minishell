/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:36:11 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/22 07:37:18 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_string_tab(t_data *data, t_env *env)
{
	char	*tmp;
	char	*str;

	if (env->equals == EQUALS)
	{
		str = ft_strjoin(env->name, "=");
		if (!str)
			ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
		if (env->content != NULL)
		{
			tmp = str;
			str = ft_strjoin(tmp, env->content);
			if (!str)
				free_exit_env(data, tmp, NULL, 1);
			free (tmp);
		}
	}
	else
	{
		str = ft_strdup(env->name);
		if (!str)
			ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
	}
	return (str);
}

char	**get_env_tab(t_data *data)
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
		tab[len] = get_string_tab(data, tmp_env);
		tmp_env = tmp_env->next;
		len++;
	}
	return (tab);
}
