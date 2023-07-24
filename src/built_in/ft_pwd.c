/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:16:57 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/24 14:41:24 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(t_data *data)
{
	ft_putstr_fd(data->pwd->content, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}
