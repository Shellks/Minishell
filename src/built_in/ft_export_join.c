/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:44:23 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/25 15:16:23 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	create_new_join_env(t_data *data, char *parse, int end)
{
	t_env	*new;
	char	*name;
	char	*content;

	name = ft_strndup(parse, data->count - 1);
	if (!name)
		ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
	if (is_valid_char(name) == false)
		return (ft_print_export_error(parse), free(name), false);
	if (parse[data->count + 1])
	{
		content = ft_strndup(&parse[data->count + 1], (end - data->count));
		if (!content)
			free_exit_env(data, name, NULL, 1);
		new = ft_env_new(name, content, EQUALS);
		if (!new)
			free_exit_env(data, name, content, 2);
	}
	else
		new = create_empty_env(data, name);
	ft_env_add_back(&data->env, new);
	return (true);
}

static bool	export_join_loop(t_data *data, t_env *env, char *parse)
{
	char	*tmp;

	if (ft_strncmp(env->name, parse, ft_strlen(env->name)) == 0 && \
	(int)ft_strlen(env->name) == (data->count - 1))
	{
		if (parse[data->count + 1])
		{
			if (env->content)
			{
				tmp = ft_strjoin(env->content, &parse[data->count + 1]);
				if (!tmp)
					ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
				free(env->content);
				env->content = tmp;
			}
			else
			{
				env->content = ft_strdup(&parse[data->count + 1]);
				if (!env->content)
					ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
			}
		}
		return (true);
	}
	return (false);
}

bool	export_join_content(t_data *data, char *parse, int end)
{
	t_env	*env;

	env = data->env;
	while (env)
	{
		if (export_join_loop(data, env, parse) == true)
			return (true);
		env = env->next;
	}
	if (create_new_join_env(data, parse, end) == false)
		return (false);
	return (false);
}
