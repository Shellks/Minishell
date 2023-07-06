/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:23:30 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/06 14:24:11 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void    is_not_exit_digit(t_data *data, t_parser  *cur, int i)
{
    if (data->env)
        ft_env_clear(&data->env);
    if (data->lexer)
        ft_lexer_clear(&data->lexer);
    printf("minishell: exit: %s: digital arguments required\n", cur->cmd[i]);
    if (data->parser)
        ft_parser_clear(&data->parser);
    exit (2);
}

static void    is_exit_digit(t_data *data, int i)
{
    int res;

    res = ft_atoi(data->parser->cmd[i]);
    if (res > 255 || res < 0)
    {
        if (data->env)
            ft_env_clear(&data->env);
        if (data->lexer)
            ft_lexer_clear(&data->lexer);
        if (data->parser)
            ft_parser_clear(&data->parser);
        exit (res % 256);
    }
    else
    {
        if (data->env)
            ft_env_clear(&data->env);
        if (data->lexer)
            ft_lexer_clear(&data->lexer);
        if (data->parser)
            ft_parser_clear(&data->parser);
        exit (res);
    }
}
static void    check_exit_args(t_data *data, t_parser  *cur, int i)
{
    int j;

    j = 0;
    while(cur->cmd[i][j])
    {
        if (cur->cmd[i][j] >= 48 && data->parser->cmd[i][j] <= 57)
            j++;
        else
            is_not_exit_digit(data, cur, i);
    }
    is_exit_digit(data, i);
}
void    ft_exit(t_data *data)
{
    int i;

    i = 1;
    if (data->parser->cmd[i])
        check_exit_args(data, data->parser, i);
    if (data->env)
        ft_env_clear(&data->env);
    if (data->lexer)
        ft_lexer_clear(&data->lexer);
    if (data->parser)
        ft_parser_clear(&data->parser);
    exit (g_status);
}
