/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:29:26 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/10 12:33:54 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    ft_close_here_doc(t_exec *exec, int *fd, int sign)
{
    if (sign == 1)
    {
        close(exec->here_doc[0]);
        close(exec->here_doc[1]);
    }
    if (sign == 2)
    {
        close(fd[0]);
        close(fd[1]);
    }
    if (sign == 3)
    {
        close(exec->here_doc[0]);
        close(exec->here_doc[1]);
        close(fd[0]);
        close(fd[1]);
    }
}