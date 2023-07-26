/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:16:57 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/26 17:00:02 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(t_data *data)
{
	ft_putstr_fd(data->pwd->content, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}
