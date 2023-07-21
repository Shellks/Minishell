/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:19:18 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/21 12:43:03 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**bubble_sort_tab(char **tab, int len)
{
    char    *tmp;
    int     i;
    int     j;

    i = 0;
    while (tab[i] && i < len)
    {
        j = 0;
        while (j < len - i - 1)
        {
            if (ft_strcmp(tab[j], tab[j + 1]) > 0)
            {
                    tmp = tab[j];
                    tab[j] = tab[j + 1];
                    tab[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }
    return (tab);
}

char    **get_env_tab(t_data *data)
{
    t_env   *tmp_env;
    char    *str;
    char    **tab;
    int     len;

    tmp_env = data->env;
    len = ft_env_size(tmp_env);
    tab = (char **)ft_calloc(sizeof(char *), len + 1);
    if (!tab)
        ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
    len = 0;
    while (tmp_env)
    {
        if (tmp_env->equals == EQUALS)
        {
            str = ft_strjoin(tmp_env->name, "=");
            if (!str)
                ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
            tab[len] = ft_strjoin(str, tmp_env->content);
            if (!tab[len])
                free_exit_env(data, str, NULL, 1);
            free (str);
        }
        else
        {
            tab[len] = ft_strdup(tmp_env->name);
            if (!tab[len])
                ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
        }
        tmp_env = tmp_env->next;
        len++;
    }
    return (tab);
}

void    ft_export_no_args(t_data *data)
{
    char    **env_tab;
    int     i;
    int     len;

    env_tab = get_env_tab(data);
    len = 0;
    while (env_tab[len])
        len++;
    env_tab = bubble_sort_tab(env_tab, len);
    i = 0;
    while (env_tab[i])
    {
        if (ft_strlen(env_tab[i]) == 1 && env_tab[i][0] == '_')
        {
            if (env_tab[++i])
                continue ;
            else
                break ; 
        }
        printf("declare -x %s\n", env_tab[i]);
        i++;
    }
    ft_free_split(env_tab);
}
