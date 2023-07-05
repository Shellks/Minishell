/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:15:36 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/05 16:41:46 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ft_unset(t_data *data, t_parser *parser)
{
    t_env       *tmp_env;
    t_parser    *tmp_parser;
    int         i;
    int         len;

    i = 1;
    tmp_env = data->env;
    tmp_parser = parser;
    if (!tmp_env || !tmp_parser->cmd[i])
        return ;
    while (tmp_parser->cmd[i])
    {
        tmp_env = data->env;
        while (tmp_env)
        {
            len = ft_strlen(tmp_parser->cmd[i]);
            if (ft_strncmp(tmp_parser->cmd[i], tmp_env->name, len) == 0)
            {
                if (!tmp_env->previous)
                    data->env = data->env->next;
                ft_env_delone(tmp_env);
                break;
            }
            else
                tmp_env = tmp_env->next;
        }
        i++;
    }
}