/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:42:40 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/08 09:44:49 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void	get_path(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	data->path = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PATH", 4) == 0)
		{
			data->path = ft_split(tmp->content, ':');
			if (!data->path)
				ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
			break ;
		}
		tmp = tmp->next;
	}
}

static t_env	*get_env(t_data *data, char *env)
{
	t_env	*new;
	char	*name;
	char	*content;
	int		len;
	int		i;

	len = 0;
	while (env[len] != '=')
		len++;
	name = ft_strndup(env, len);
	if (!name)
		ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
	len++;
	i = len;
	while (env[len])
		len++;
	content = ft_strndup(&env[i], (len - i));
	if (!content)
		free_exit_env(data, name, NULL, 1);
	new = ft_env_new(name, content);
	if (!new)
		free_exit_env(data, name, content, 2);
	return (new);
}

void	set_env(t_data *data, char **env)
{
	t_env	*new;
	int		tmp;
	int		i;

	i = 0;
	data->env = NULL;
	while (env[i])
	{
		new = get_env(data, env[i++]);
		if (ft_strncmp(new->name, "SHLVL", 5) == 0)
		{
			tmp = ft_atoi(new->content);
			tmp++;
			free(new->content);
			new->content = ft_itoa(tmp);
			if (!new->content)
				ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
		}
		ft_env_add_back(&data->env, new);
	}
	get_pwd(data);
	get_path(data);
}
