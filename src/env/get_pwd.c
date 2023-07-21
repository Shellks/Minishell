/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:05:05 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/21 17:29:18 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	create_old_pwd(t_data *data)
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

static void	create_pwd(t_data *data)
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

static void	create_shlvl(t_data *data)
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

static void	set_pwd(t_data *data, int flag_pwd, int flag_shlvl)
{
	if (flag_shlvl == 0)
		create_shlvl(data);
	if (flag_pwd == 0)
	{
		create_old_pwd(data);
		create_pwd(data);
	}
	if (flag_pwd == 1)
		create_old_pwd(data);
	if (flag_pwd == 2)
		create_pwd(data);
}

void	get_pwd(t_data *data)
{
	t_env	*tmp;
	int		flag_pwd;
	int		flag_shlvl;

	flag_pwd = 0;
	flag_shlvl = 0;
	tmp = data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PWD", 3) == 0)
		{
			flag_pwd += 1;
			data->pwd = tmp;
		}
		if (ft_strncmp(tmp->name, "OLDPWD", 6) == 0)
		{
			flag_pwd += 2;
			data->old_pwd = tmp;
		}
		if (ft_strncmp(tmp->name, "SHLVL", 5) == 0)
			flag_shlvl += 1;
		tmp = tmp->next;
	}
	set_pwd(data, flag_pwd, flag_shlvl);
}
