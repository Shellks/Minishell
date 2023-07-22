/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_exist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 08:20:02 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/22 08:20:48 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	export_is_exist(t_data *data, t_parser *parser, t_env * env, int end)
{
	int		i;

	i = data->count;
	free(env->content);
	if (parser->cmd[1][i] == '=')
	{
		if (env->equals == NOT_EQUALS)
			env->equals = EQUALS;
		if (parser->cmd[1][i + 1])
		{
			env->content = ft_strndup(&parser->cmd[1][i + 1], (end - i));
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

bool	ft_check_export_exist(t_data *data, t_parser *parser, int end)
{
	t_env	*tmp_env;
	int		i;

	tmp_env = data->env;
	i = data->count;
	while (tmp_env)
	{
		if (ft_strncmp(tmp_env->name, parser->cmd[1], i) == 0)
		{
			export_is_exist(data, parser, tmp_env, end);
			return (true);
		}
		tmp_env = tmp_env->next;
	}
	return (false);
}
