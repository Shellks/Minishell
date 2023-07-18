/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:19:18 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/18 12:08:49 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


//besoin de fix le bubble sort je pense que je modifie mal les pointeurs
static t_env    *bubble_sort_list(t_env *env)
{
	t_env	*start;
    t_env   *to_sort;
    int     i;
    int     len;
    
    i = 0;
	start = env;
    len = ((ft_env_size(env) + 1));
    to_sort = env;
    while(env && --len != 0)
    {
        if (to_sort->name[0] > env->name[0])
            to_sort = env;
        if (!env->next || i <= len)
        {
            if (to_sort->previous)
			    to_sort->previous->next = to_sort->next;
		    if (to_sort->next)
			    to_sort->next->previous = to_sort->previous;
            ft_env_add_back(&env, to_sort);
            env = start;
            i = 0;
        }
        else
            env = env->next;
        printf("env->name = %s\n", env->name);
    }
    return (env);
}

void    ft_export_no_args(t_env *env)
{
    t_env   *sorted_env;

    sorted_env = bubble_sort_list(env);
    ft_env_first(env);
    while (sorted_env)
    {
        printf("Boug!\n");
        // if (ft_strncmp(env->name, "_", 1))
        // {
        //     env = env->next;
        //     continue ;
        // }
        if (sorted_env->equals == NOT_EQUALS)
            printf("declare -x %s\n", sorted_env->name);
        else
            printf("declare -x %s=\"%s\"\n", sorted_env->name, sorted_env->content);
        sorted_env = sorted_env->next;
    }
}
