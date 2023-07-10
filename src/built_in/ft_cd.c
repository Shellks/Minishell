/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbernard <nicolasbernard@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 17:38:10 by nicolasbern       #+#    #+#             */
/*   Updated: 2023/07/10 00:42:21 by nicolasbern      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char    *get_target_env(t_env *env, char *name)
{
    t_env   *env_tmp;
    char    *target;

    env_tmp = NULL;
    env_tmp = env;
    target = NULL;
    while (env_tmp)
	{
        if (ft_strcmp(env_tmp->name, name) == 0)
            target = ft_strdup(env_tmp->content);
		env_tmp = env_tmp->next;
	}
    return (target);
}

bool    actualise_pwd(t_data *data, char *name, char *target)
{
    t_env   *env_tmp;

    env_tmp = NULL;
    env_tmp = data->env;
    while (env_tmp)
	{
        if (ft_strcmp(env_tmp->name, name) == 0)
        {
            if (ft_strncmp(name, "OLDPWD", 6) == 0)
            {
                free(env_tmp->content);
                env_tmp->content = ft_strdup(target);
                free (target);
                return (true);
            }
            else
            {
                free(env_tmp->content);
                env_tmp->content = ft_strdup(target);
                free (target);
                return (true);
            }    
        }
		env_tmp = env_tmp->next;
	}
    return (false);
}

bool    cd_and_actualise_env(t_data *data, char *target)
{
    char *pwd;

    pwd = getcwd(NULL, 0);
    if (pwd != NULL)
        if (actualise_pwd(data, "OLDPWD", pwd) == false)
            return (false);
    if (chdir(target) != 0)
    {
        ft_putstr_fd("cd: ", 2); 
        ft_putstr_fd(target, 2); 
        ft_putstr_fd(" ", 2); 
        perror("");
        return (false);
    }
    pwd = getcwd(NULL, 0);
    if (pwd != NULL)
        if (actualise_pwd(data, "PWD", pwd) == false)
            return (false);
    return (true);  
}

bool    ft_cd(t_data *data, char **tab)
{
    char    *target;

    target = NULL;
    if (ft_strlen_tab(tab) > 2)
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        return (false);
    }
    else if (ft_strlen_tab(tab) == 1 || ft_strcmp(tab[1], "~") == 0)
        target = get_target_env(data->env, "HOME");
    else if (ft_strcmp(tab[1], "-") == 0)
        target = get_target_env(data->env, "OLDPWD");
    else
        target = ft_strdup(tab[1]);
    if (target == NULL)
        return (false);
    if (cd_and_actualise_env(data, target) == false)
        return (false);
    return (true);
}