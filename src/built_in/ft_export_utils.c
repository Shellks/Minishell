/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:19:18 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/18 16:51:45 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



static void swap_nodes(t_env *node1, t_env *node2)
{
    if (node1->previous != NULL)
        node1->previous->next = node2;
    if (node2->next != NULL)
        node2->next->previous = node1;
    node1->next = node2->next;
    node2->previous = node1->previous;
    node1->previous = node2;
    node2->next = node1;
}

static t_env *export_sort_list(t_env *env)
{
    t_env *start = env;
    int swapped = 1;

    while (swapped) 
    {
        swapped = 0;
        while (env && env->next) 
        {
            if (ft_strcmp(env->name, env->next->name) > 0) 
            {
                swap_nodes(env, env->next);
                swapped = 1;
            }
            env = env->next;
        }
        if (swapped)
            env = start;
    }
    return start;
}

t_env   *copy_linked_list(t_data *data, t_env *env)
{
    t_env   *new_env;
    t_env   *node;
    char    *name;
    char    *content;
    t_equals    equals;

    new_env = NULL;
    new_env = malloc(sizeof(t_env));
    if (!new_env)
        ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
    while (env)
    {
        content = NULL;
        name = ft_strdup(env->name);
        if (!name)
            ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
        content = ft_strdup(env->content);
            if (!content)
                free_exit_env(data, name, NULL, 1);
        equals = env->equals;
        node = ft_env_new(name, content, equals);
        if (!node)
            free_exit_env(data, name, content, 1);
        ft_env_add_back(&new_env, node);
        env = env->next;
    }
    return (new_env->next);
}

void    ft_export_no_args(t_data *data, t_env *env)
{
    t_env   *tmp_env;
    t_env   *env_copy;
    t_env   *sorted_env;

    tmp_env = env;
    env_copy = copy_linked_list(data, tmp_env);
    sorted_env = export_sort_list(env_copy);
    tmp_env = sorted_env;
    while (sorted_env)
    {
        if (ft_strlen(sorted_env->name) == 1 && sorted_env->name[0] == '_')
        {
            if (env->next)
            {
                env = env->next;
                continue ;
            }
            else
                break ; 
        }
        if (sorted_env->equals == NOT_EQUALS)
            printf("declare -x %s\n", sorted_env->name);
        else
            printf("declare -x %s=\"%s\"\n", sorted_env->name, sorted_env->content);
        sorted_env = sorted_env->next;
    }
    ft_env_clear(&tmp_env);
}
