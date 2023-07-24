/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:05:05 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/24 14:50:16 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	set_new_env(t_data *data, int pwd, int shlvl, int usr)
{
	if (shlvl == 0)
		create_shlvl(data);
	if (pwd == 0)
	{
		create_old_pwd(data);
		create_pwd(data);
	}
	if (pwd == 1)
		create_old_pwd(data);
	if (pwd == 2)
		create_pwd(data);
	if (usr == 0)
		create_usr_env(data);
}

static int	get_pwd_loop(t_data *data, t_env *tmp, int *pwd, int *usr)
{
	int	shlvl;

	shlvl = 0;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PWD", 3) == 0)
		{
			*pwd += 1;
			data->pwd = tmp;
		}
		if (ft_strncmp(tmp->name, "OLDPWD", 6) == 0)
		{
			*pwd += 2;
			data->old_pwd = tmp;
		}
		if (ft_strncmp(tmp->name, "SHLVL", 5) == 0)
			shlvl += 1;
		if (ft_strncmp(tmp->name, "_", 5) == 0)
			*usr += 1;
		tmp = tmp->next;
	}
	return (shlvl);
}

void	get_pwd(t_data *data)
{
	t_env	*tmp;
	int		flag_pwd;
	int		flag_shlvl;
	int		flag_usr;

	flag_pwd = 0;
	flag_shlvl = 0;
	flag_usr = 0;
	tmp = data->env;
	flag_shlvl = get_pwd_loop(data, tmp, &flag_pwd, &flag_usr);
	if (flag_pwd != 3 || flag_shlvl != 1 || flag_usr != 1)
		set_new_env(data, flag_pwd, flag_shlvl, flag_usr);
}
