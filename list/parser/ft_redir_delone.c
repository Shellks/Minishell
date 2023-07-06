/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_delone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:27:25 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/06 14:13:48 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_redir_delone(t_redir *lst)
{
	if (lst)
	{
		free(lst->redirec);
		free(lst);
	}
}