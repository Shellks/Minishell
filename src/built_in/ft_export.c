/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:51:54 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/21 17:49:54 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_print_id_error(char *word)
{
	printf("minishell: export: « %s »: invalid identifier\n", word);
}

static  bool	is_valid_char(t_parser *parser, char *name, int i)
{
	if (i == 0)
	{
		if (name[0] >= 48 && name[0] <= 57)
			return (ft_print_id_error(parser->cmd[1]), false);
	}
	if (name[i] == '_')
		return (true);
	if (name[i] < 48 || (name[i] > 57 && name[i] < 65))
		return (false);
	if ((name[i] > 90 && name[i] < 97) || name[i] > 122)
		return (false);
	return (true);
}

static bool	create_new_env(t_data *data, t_parser *parser, int end, int i)
{
	int		j;
	t_env	*new;
	char	*name;
	char	*content;

	j = -1;
	name = ft_strndup(parser->cmd[1], i);
	if (!name)
		ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
	while (name[++j])
		if (is_valid_char(parser, name, j) == false)
			return (ft_print_id_error(parser->cmd[1]), false);
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
	{
		new = ft_env_new(name, NULL, EQUALS);
		if (!new)
			free_exit_env(data, name, NULL, 1);
	}
	ft_env_add_back(&data->env, new);
	return (true);
}

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

static bool	ft_check_export_exist(t_data *data, t_parser *parser, int end)
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
		return (ft_print_id_error(parser->cmd[1]), false);
	}
	data->count = -1;
	while (name[++data->count])
	{
		if (is_valid_char(parser, name, data->count) == false)
		{
			free(name);
			return (ft_print_id_error(parser->cmd[1]), false);
		}
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
		return(ft_export_no_args(data), true);
	end = (ft_strlen(tmp_parser->cmd[1]) - 1);
	while(tmp_parser->cmd[1][data->count] && tmp_parser->cmd[1][data->count] != '=')
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
