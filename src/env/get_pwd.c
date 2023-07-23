/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbernard <nicolasbernard@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:05:05 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/23 16:02:43 by nicolasbern      ###   ########.fr       */
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
//=================mini_env================
//bad msg if env -i and cmd : 	minishell: ls: no such file or directory     	not good
//								msh: sleep: command not found					good
// check if leaks
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

static void	create_usr_env(t_data *data)
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


static void	set_mini_env(t_data *data, int flag)
{
	if (flag == 0)
	{
		//echo $OLDPWD = segfault
		//create_old_pwd(data);
		create_pwd(data);
	}
	if (flag == 1)
		create_old_pwd(data);
	if (flag == 2)
		create_pwd(data);
	create_shlvl(data);
	create_usr_env(data);
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
	//if env -i -> flag always 0 ?
	if (flag != 3)
		set_mini_env(data, flag);
}
