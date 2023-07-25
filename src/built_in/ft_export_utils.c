/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:19:18 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/25 15:16:41 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	export_is_exist(t_data *data, char *parse, t_env *env, int end)
{
	int	i;

	i = data->count;
	free(env->content);
	if (parse[i] == '=')
	{
		if (env->equals == NOT_EQUALS)
			env->equals = EQUALS;
		if (parse[i + 1])
		{
			env->content = ft_strndup(&parse[i + 1], (end - i));
			if (!env->content)
				ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
		}
		else
			env->content = NULL;
	}
	else
	{
		if (env->equals == EQUALS)
			env->equals = NOT_EQUALS;
		env->content = NULL;
	}
}

bool	ft_check_export_exist(t_data *data, char *parse, int end)
{
	t_env	*env;
	int		i;

	(void)end;
	env = data->env;
	i = data->count;
	while (env)
	{
		if (ft_strncmp(env->name, parse, ft_strlen(env->name)) == 0 && \
		(int)ft_strlen(env->name) == data->count)
		{
			export_is_exist(data, parse, env, end);
			return (true);
		}
		env = env->next;
	}
	return (false);
}

bool	is_valid_char(char *name)
{
	int	i;

	i = -1;
	while (name[++i])
	{
		if (i == 0)
		{
			if (name[0] == '=')
				return (false);
			if (name[0] >= 48 && name[0] <= 57)
				return (false);
		}
		if (name[i] == '_')
			continue ;
		if (name[i] < 48 || (name[i] > 57 && name[i] < 65))
			return (false);
		if ((name[i] > 90 && name[i] < 97) || name[i] > 122)
			return (false);
	}
	return (true);
}

t_env	*create_empty_env(t_data *data, char *name)
{
	t_env	*new;

	new = ft_env_new(name, NULL, EQUALS);
	if (!new)
		free_exit_env(data, name, NULL, 1);
	return (new);
}
