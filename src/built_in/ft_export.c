/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:51:54 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/27 15:43:23 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	create_new_env(t_data *data, char *parse, int end, int i)
{
	t_env	*new;
	char	*name;
	char	*content;

	name = ft_strndup(parse, i);
	if (!name)
		ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
	if (is_valid_char(name) == false || !parse[0])
		return (ft_print_export_error(parse), free(name), false);
	if (parse[i + 1])
	{
		content = ft_strndup(&parse[i + 1], (end - i));
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

static bool	create_env_no_equals(t_data *data, char *parse)
{
	t_env	*new;
	char	*name;

	name = ft_strdup(parse);
	if (!name)
		ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
	if (name[0] >= 48 && name[0] <= 57)
	{
		free(name);
		return (ft_print_export_error(parse), false);
	}
	if (is_valid_char(name) == false || !parse[0])
	{
		free(name);
		return (ft_print_export_error(parse), false);
	}
	new = ft_env_new(name, NULL, NOT_EQUALS);
	if (!new)
		free_exit_env(data, name, NULL, 1);
	ft_env_add_back(&data->env, new);
	return (true);
}

static void	ft_export_loop(t_data *data, char *parser, int end)
{
	if (ft_check_export_exist(data, parser, end) == true)
		return ;
	if (parser[data->count] != '=')
	{
		if (create_env_no_equals(data, parser) == false)
			g_status = 1;
		return ;
	}
	if (parser[data->count] == '=' && parser[data->count - 1] == '+')
	{
		if (parser[0] == '+' && parser[1] == '=')
		{
			ft_print_export_error(parser);
			g_status = 1;
			return ;
		}
		if (export_join_content(data, parser, end) == false)
			g_status = 1;
		return ;
	}
	if (create_new_env(data, parser, end, data->count) == false)
		g_status = 1;
}

void	ft_export(t_data *data, t_parser *parser)
{
	int			end;
	int			i;

	if (!parser->cmd[1])
		return (ft_print_export_sort(data));
	i = 0;
	while (parser->cmd[++i])
	{
		data->count = 0;
		if (parser->cmd[i][0] == '=' || \
		(parser->cmd[i][0] == '+' && parser->cmd[i][1] == '='))
		{
			ft_print_export_error(parser->cmd[i]);
			g_status = 1;
			continue ;
		}
		end = (ft_strlen(parser->cmd[i]) - 1);
		while (parser->cmd[i][data->count] && \
		parser->cmd[i][data->count] != '=')
			data->count++;
		ft_export_loop(data, parser->cmd[i], end);
	}
}
