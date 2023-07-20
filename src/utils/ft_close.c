/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:29:26 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/20 13:30:07 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_close_here_doc(int *fd, int sign)
{
	if (sign == 2)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (sign == 3)
	{
		close(fd[0]);
		close(fd[1]);
	}
}
