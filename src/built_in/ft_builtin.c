/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:10:21 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/27 13:16:39 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	check_is_builtin(t_parser *parse)
{
	if (!ft_strncmp(parse->cmd[0], "pwd", 3) && \
	(int)ft_strlen(parse->cmd[0]) == 3)
		return (true);
	else if (!ft_strncmp(parse->cmd[0], "unset", 5) && \
	(int)ft_strlen(parse->cmd[0]) == 5)
		return (true);
	else if (!ft_strncmp(parse->cmd[0], "export", 6) && \
	(int)ft_strlen(parse->cmd[0]) == 6)
		return (true);
	else if (!ft_strncmp(parse->cmd[0], "exit", 4) && \
	(int)ft_strlen(parse->cmd[0]) == 4)
		return (true);
	else if (!ft_strncmp(parse->cmd[0], "env", 3) && \
	(int)ft_strlen(parse->cmd[0]) == 3)
		return (true);
	else if (!ft_strncmp(parse->cmd[0], "echo", 4) && \
	(int)ft_strlen(parse->cmd[0]) == 4)
		return (true);
	else if (!ft_strncmp(parse->cmd[0], "cd", 2) && \
	(int)ft_strlen(parse->cmd[0]) == 2)
		return (true);
	return (false);
}