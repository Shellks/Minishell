/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:15:36 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/14 12:25:30 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void    unset_loop(t_data *data, t_env *env, t_parser *parser, int i)
{
//    int j;

    while (env)
    {
    //    j = ft_strlen(parser->cmd[i]);
        if (ft_strncmp(parser->cmd[i], env->name, ft_strlen(env->name)) == 0)
        {
            if (!env->previous)
                data->env = data->env->next;
            ft_env_delone(env);
            break;
        }
         else
            env = env->next;
    }
}

bool    ft_unset(t_data *data, t_parser *parser)
{
    t_env       *tmp_env;
    t_parser    *tmp_parser;
    int         i;

    i = 1;
    tmp_env = data->env;
    tmp_parser = parser;
    //need peut-etre la verif de var qui sont en readonly
    if (!tmp_parser->cmd[i])
    {
        printf("unset: not enough arguments\n");
        return (false);
    }
    if (!tmp_env)
        return (false);
    while (tmp_parser->cmd[i])
    {
        tmp_env = data->env;
        unset_loop(data, tmp_env, tmp_parser, i);
        i++;
    }
    return (true);
}
