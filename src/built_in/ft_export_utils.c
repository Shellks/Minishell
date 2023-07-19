/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:19:18 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/19 11:29:33 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char    **bubble_sort_tab(char **tab, int len)
{
    char    *tmp;
    char    *to_sort;
    int     i;
    int     j;

    i = 0;
    while (tab[i] && i < len)
    {
        to_sort = tab[i];
        j = -1;
        while(tab[++j] && j < len - i)
        {
            if (ft_strcmp(tab[j], to_sort) > 0)
            {
                printf("tab[j] = %s\n", tab[j]);
                printf("to_sort = %s\n", to_sort);
                tmp = tab[j];
                tab[j] = to_sort;
                to_sort = tmp;
            }
        }
        i++;
    }
    return (tab);
}

char    **get_env_tab(t_data *data, t_env * env)
{
    char    *str;
    char    **tab;
    int     len;

    len = ft_env_size(env);
    tab = (char **)ft_calloc(sizeof(char *), len + 1);
    if (!tab)
        ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
    len = 0;
    while (env)
    {
        if (env->equals == EQUALS)
        {
            str = ft_strjoin(env->name, "=");
            if (!str)
                ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
            tab[len] = ft_strjoin(str, env->content);
            if (!tab[len])
                free_exit_env(data, str, NULL, 1);
            free (str);
        }
        else
        {
            tab[len] = ft_strdup(env->name);
            if (!tab[len])
                ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
        }
        env = env->next;
        len++;
    }
    return (tab);
}

void    ft_export_no_args(t_data *data, t_env *env)
{
    char    **env_tab;
    t_env   *tmp_env;
    int     i;
    int     len;

    tmp_env = env;
    env_tab = get_env_tab(data, tmp_env);
    len = 0;
    while (env_tab[len])
        len++;
    env_tab = bubble_sort_tab(env_tab, len);
    i = 0;
    while (env_tab[i])
    {
        if (ft_strlen(env_tab[i]) == 1 && env_tab[i][0] == '_')
        {
            if (env_tab[i + 1])
            {
                i++;
                continue ;
            }
            else
                break ; 
        }
        printf("declare -x %s\n", env_tab[i]);
        i++;
    }
    // if (env_tab)
    //     ft_free_split(env_tab);
}
