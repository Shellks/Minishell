/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_delone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:32:36 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/05 16:29:01 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env_delone(t_env *lst)
{
	if (lst)
    {
        t_env *current = lst;
        if (current->previous)
            current->previous->next = current->next;
        if (current->next)
            current->next->previous = current->previous;

        if (lst == current) // Si la node est la première node
            lst = current->next; // Mettre à jour le pointeur de la liste

        free(current->name);
        free(current->content);
        free(current);
    }
}
