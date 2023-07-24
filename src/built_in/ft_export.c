/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:51:54 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/24 14:41:04 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	is_valid_char(t_parser *parser, char *name)
{
	int	i;

	i = -1;
	while (name[++i])
	{
		if (i == 0)
		{
			if (name[0] >= 48 && name[0] <= 57)
				return (ft_print_export_error(parser->cmd[1]), false);
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

static t_env	*create_empty_env(t_data *data, char *name)
{
	t_env	*new;

	new = ft_env_new(name, NULL, EQUALS);
	if (!new)
		free_exit_env(data, name, NULL, 1);
	return (new);
}

static bool	create_new_env(t_data *data, t_parser *parser, int end, int i)
{
	t_env	*new;
	char	*name;
	char	*content;

	name = ft_strndup(parser->cmd[1], i);
	if (!name)
		ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
	if (is_valid_char(parser, name) == false)
		return (ft_print_export_error(parser->cmd[1]), free(name), false);
	if (parser->cmd[1][i + 1])
	{
		content = ft_strndup(&parser->cmd[1][i + 1], (end - i));
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

static bool	create_env_no_equals(t_data *data, t_parser *parser)
{
	t_env	*new;
	char	*name;

	name = ft_strdup(parser->cmd[1]);
	if (!name)
		ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
	if (name[0] >= 48 && name[0] <= 57)
	{
		free(name);
		return (ft_print_export_error(parser->cmd[1]), false);
	}
	if (is_valid_char(parser, name) == false)
	{
		free(name);
		return (ft_print_export_error(parser->cmd[1]), false);
	}
	new = ft_env_new(name, NULL, NOT_EQUALS);
	if (!new)
		free_exit_env(data, name, NULL, 1);
	ft_env_add_back(&data->env, new);
	return (true);
}

bool	ft_export(t_data *data, t_parser *parser)
{
	t_parser	*tmp_parser;
	int			end;

	data->count = 0;
	tmp_parser = parser;
	if (!data->env)
		return (false);
	if (!tmp_parser->cmd[1])
		return (ft_export_no_args(data), true);
	end = (ft_strlen(tmp_parser->cmd[1]) - 1);
	while (tmp_parser->cmd[1][data->count] && \
	tmp_parser->cmd[1][data->count] != '=')
		data->count++;
	if (ft_check_export_exist(data, tmp_parser, end) == true)
		return (true);
	if (tmp_parser->cmd[1][data->count] != '=')
	{
		if (create_env_no_equals(data, tmp_parser) == true)
			return (true);
		else
			return (false);
	}
	if (create_new_env(data, tmp_parser, end, data->count) == false)
		return (false);
	return (true);
}
