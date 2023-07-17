/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:05:05 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/17 23:47:15 by acarlott         ###   ########lyon.fr   */
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

static void	set_pwd(t_data *data, int flag)
{
	if (flag == 0)
	{
		create_old_pwd(data);
		create_pwd(data);
	}
	if (flag == 1)
		create_old_pwd(data);
	if (flag == 2)
		create_pwd(data);
}

void	get_pwd(t_data *data)
{
	t_env	*tmp;
	int		flag;

	flag = 0;
	tmp = data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PWD", 3) == 0)
		{
			flag += 1;
			data->pwd = tmp;
		}
		if (ft_strncmp(tmp->name, "OLDPWD", 6) == 0)
		{
			flag += 2;
			data->old_pwd = tmp;
		}
		tmp = tmp->next;
	}
	if (flag != 3)
		set_pwd(data, flag);
}
