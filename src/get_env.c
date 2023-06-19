/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:42:40 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/19 16:39:06 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	int	get_path(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	data->path = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PATH", 4) == 0)
		{
			data->path = ft_split(tmp->content, ':');
			if (data->path == NULL)
				return (ERR_MALLOC);
			break ;
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

static t_env	*get_env(char *env)
{
	char	*name;
	char	*content;
	int		len;
	int		i;
	int		j;

	len = 0;
	i = -1;
	while (env[len] != '=')
		len++;
	name = (char *)ft_calloc(sizeof(char *), len + 1);
	if (!name)
		return (NULL);
	while (++i < len)
		name[i] = env[i];
	len++;
	while (env[len])
		len++;
	content = (char *)ft_calloc(sizeof(char *), (len - i));
	if (!content)
		return (free(name), NULL);
	j = -1;
	while (++i < len)
		content[++j] = env[i];
	return (ft_env_new(name, content));
}

void	set_env(t_data *data, char **env)
{
	t_env	*new;
	int		i;

	i = 0;
	data->env = NULL;
	while (env[i])
	{
		new = get_env(env[i++]);
		if (!new)
			ft_free(data, ERR_MALLOC, "Malloc_error");
		ft_env_add_back(&data->env, new);
	}
	get_pwd(data);
	if (get_path(data) == ERR_MALLOC)
		ft_free(data, ERR_MALLOC, "Malloc_error");
}
