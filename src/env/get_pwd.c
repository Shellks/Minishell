/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:05:05 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/24 11:23:19 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	set_new_env(t_data *data, int flag)
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
	if (flag != 3)
		set_new_env(data, flag);
}
