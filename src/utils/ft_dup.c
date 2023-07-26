/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 22:18:45 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/26 22:03:40 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_dup(t_data *data, int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		close(fd1);
		ft_free_exit(data, ERR_DUP, "Error with creating dup\n");
	}
	close(fd1);
}
