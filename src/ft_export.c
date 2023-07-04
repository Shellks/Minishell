/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:51:54 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/04 22:16:18 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_print_id_error(char *word)
{
	printf("minishell: export: « %s »: invalid identifier\n", word);
}

static  bool    is_valid_char(char *name, int i)
{
    if (name[i] < 48 || (name[i] > 57 && name[i] < 65))
        return (false);
    if ((name[i] > 90 && name[i] < 97) || name[i] > 122)
        return (false);
    return (true);
}

static bool    create_new_env(t_data *data, t_parser *parser, int end, int i)
{
    int     j;
    t_env   *new;
    char    *name;
    char    *content;

    j = -1;
    name = ft_strndup(parser->cmd[1], i);
    if (!name)
        ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
    if (name[0] >= 48 && name[0] <= 57)
        return (ft_print_id_error(parser->cmd[1]), false);
    while (name[++j])
        if (is_valid_char(name, j) == false)
            return (ft_print_id_error(parser->cmd[1]), false);
    content = ft_strndup(&parser->cmd[1][i + 1], (end - i));
     if (!content)
         ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
    new = ft_env_new(name, content);
    if (!new)
        ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
    ft_env_add_back(&data->env, new);
    return (true);
}

static int export_is_exist(t_env *env, t_parser *parser, int end, int i)
{
    if (ft_strncmp(env->name, parser->cmd[1], i) == 0)
    {
        free(env->content);
        env->content = ft_strndup(&parser->cmd[1][i + 1], (end - i));
        if (!env->content)
            return (ERR_MALLOC);
        return (TRUE);
    }
    return (FALSE);
}

bool    ft_export(t_data *data, t_parser *parser)
{
    t_parser    *tmp_parser;
    t_env      *tmp_env;
    int         i;
    int         end;

    tmp_env = data->env;
    tmp_parser = parser;
    if (!tmp_env || !tmp_parser->cmd[1])
        return (false);
    i = 0;
    end = (ft_strlen(tmp_parser->cmd[1]) - 1);
    while(tmp_parser->cmd[1][i] && tmp_parser->cmd[1][i] != '=')
        i++;
    if (tmp_parser->cmd[1][i] != '=')
        return (false);
    while(tmp_env)
    {
        if (export_is_exist(tmp_env, tmp_parser, end, i) == TRUE)
            return (true);
        else if (export_is_exist(tmp_env, tmp_parser, end, i) == ERR_MALLOC)
            ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
        tmp_env = tmp_env->next;
    }
    if (create_new_env(data, tmp_parser, end, i) == false)
        return (false);
    return (true);
}