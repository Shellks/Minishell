/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:05:05 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/06 16:05:26 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	create_old_pwd(t_data *data)
{
	char	*name;
	char	*content;
	t_env	*new;

	name = ft_strdup("OLDPWD");
	if (!name)
		return (FALSE);
	content = NULL;
	new = ft_env_new(name, content);
	if (!new)
		return (FALSE);
	data->old_pwd = new;
	ft_env_add_back(&data->env, new);
	return (TRUE);
}

static int	create_pwd(t_data *data)
{
	char	*name;
	char	*content;
	t_env	*new;

	name = ft_strdup("PWD");
	if (!name)
		return (FALSE);
	content = getcwd(NULL, 0);
	if (!content)
	{
		free(name);
		return (FALSE);
	}
	new = ft_env_new(name, content);
	if (!new)
		return (FALSE);
	data->pwd = new;
	ft_env_add_back(&data->env, new);
	return (TRUE);
}

static int	set_pwd(t_data *data, int flag)
{
	if (flag == 0)
	{
		if (create_old_pwd(data) == FALSE)
			return (FALSE);
		if (create_pwd(data) == FALSE)
			return (FALSE);
	}
	if (flag == 1)
		if (create_old_pwd(data) == FALSE)
			return (FALSE);
	if (flag == 2)
		if (create_pwd(data) == FALSE)
			return (FALSE);
	return (TRUE);
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
		if (set_pwd(data, flag) == FALSE)
			ft_free(data, ERR_MALLOC, "Malloc_error", 1);
}
