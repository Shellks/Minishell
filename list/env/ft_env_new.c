/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:35:26 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/17 23:43:45 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*ft_env_new(char *name, char *content, t_equals equals)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		free(name);
		free(content);
		return (0);
	}
	new->name = name;
	new->content = content;
	new->equals = equals;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}
