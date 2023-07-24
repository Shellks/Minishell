/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:18:59 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/24 11:23:43 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_old_pwd(t_data *data)
{
	char	*name;
	char	*content;
	t_env	*new;

	name = ft_strdup("OLDPWD");
	if (!name)
		ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
	content = NULL;
	new = ft_env_new(name, content, NOT_EQUALS);
	if (!new)
		free_exit_env(data, name, NULL, 1);
	data->old_pwd = new;
	ft_env_add_back(&data->env, new);
}

void	create_pwd(t_data *data)
{
	char	*name;
	char	*content;
	t_env	*new;

	name = ft_strdup("PWD");
	if (!name)
		ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
	content = getcwd(NULL, 0);
	if (!content)
		free_exit_env(data, name, NULL, 1);
	new = ft_env_new(name, content, EQUALS);
	if (!new)
		free_exit_env(data, name, content, 2);
	data->pwd = new;
	ft_env_add_back(&data->env, new);
}

void	create_shlvl(t_data *data)
{
	char	*name;
	char	*content;
	t_env	*new;

	name = ft_strdup("SHLVL");
	if (!name)
		ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
	content = ft_strdup("1");
	if (!content)
		free_exit_env(data, name, NULL, 1);
	new = ft_env_new(name, content, EQUALS);
	if (!new)
		free_exit_env(data, name, content, 2);
	ft_env_add_back(&data->env, new);
}

void	create_usr_env(t_data *data)
{
	char	*name;
	char	*content;
	t_env	*new;

	name = ft_strdup("_");
	if (!name)
		ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
	content = ft_strdup("/usr/bin/env");
	if (!content)
		free_exit_env(data, name, NULL, 1);
	new = ft_env_new(name, content, EQUALS);
	if (!new)
		free_exit_env(data, name, content, 2);
	ft_env_add_back(&data->env, new);
}
