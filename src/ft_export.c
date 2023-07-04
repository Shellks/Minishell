/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 10:51:54 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/04 15:46:12 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void    create_new_env(t_data *data, t_parser *parser, int end, int i)
{
    t_env   *new;
    char    *name;
    char    *content;

    name = ft_strndup(parser->cmd[1], i);
    if (!name)
        ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
    content = ft_strndup(&parser->cmd[1][i + 1], (end - i));
     if (!content)
         ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
    new = ft_env_new(name, content);
    if (!new)
        ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
    ft_env_add_back(&data->env, new);
}

static int export_is_exist(t_env *env, t_parser *parser, int end, int i)
{
    if (ft_strncmp(env->name, parser->cmd[1], i) == 0)
    {
        free(env->content);
        printf("parser = %c\n", parser->cmd[1][i]);
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
    create_new_env(data, tmp_parser, end, i);
    return (true);
}