/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:51:54 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/20 18:15:42 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_print_id_error(char *word)
{
	printf("minishell: export: « %s »: invalid identifier\n", word);
}

static bool	is_valid_char(char *name, int i)
{
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
	if (name[0] >= 48 && name[0] <= 57)
		return (ft_print_id_error(parser->cmd[1]), false);
	while (name[++j])
		if (is_valid_char(name, j) == false)
			return (ft_print_id_error(parser->cmd[1]), false);
	content = ft_strndup(&parser->cmd[1][i + 1], (end - i));
	if (!content)
		free_exit_env(data, name, NULL, 1);
	new = ft_env_new(name, content, EQUALS);
	if (!new)
		free_exit_env(data, name, content, 2);
	ft_env_add_back(&data->env, new);
	return (true);
}

static int	export_is_exist(t_env *env, t_parser *parser, int end, int i)
{
	if (ft_strncmp(env->name, parser->cmd[1], ft_strlen(env->name)) == 0)
	{
		free(env->content);
		env->content = ft_strndup(&parser->cmd[1][i + 1], (end - i));
		if (!env->content)
			return (ERR_MALLOC);
		return (TRUE);
	}
	return (FALSE);
}

static bool	create_env_no_equals(t_data *data, t_parser *parser)
{
	t_env	*new;
	char	*name;
	int		i;

	i = -1;
	name = ft_strdup(parser->cmd[1]);
	if (!name)
		ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
	if (name[0] >= 48 && name[0] <= 57)
	{
		free(name);
		return (ft_print_id_error(parser->cmd[1]), false);
	}
	while (name[++i])
	{
		if (is_valid_char(name, i) == false)
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
	t_env		*tmp_env;
	int			end;

	data->count = 0;
	tmp_env = data->env;
	tmp_parser = parser;
	if (!tmp_env)
		return (false);
	if (!tmp_parser->cmd[1])
		return (ft_export_no_args(data, data->env), true);
	end = (ft_strlen(tmp_parser->cmd[1]) - 1);
	while (tmp_parser->cmd[1][data->count] && tmp_parser->cmd[1][data->count] != '=')
		data->count++;
	if (tmp_parser->cmd[1][data->count] != '=')
	{
		if (create_env_no_equals(data, tmp_parser) == true)
			return (true);
		else
			return (false);
	}
	while (tmp_env)
	{
		if (export_is_exist(tmp_env, tmp_parser, end, data->count) == TRUE)
			return (true);
		else if (export_is_exist(tmp_env, tmp_parser, end, data->count) == ERR_MALLOC)
			ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
		tmp_env = tmp_env->next;
	}
	if (create_new_env(data, tmp_parser, end, data->count) == false)
		return (false);
	return (true);
}