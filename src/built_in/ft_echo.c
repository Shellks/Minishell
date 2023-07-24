/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:50:43 by nicolasbern       #+#    #+#             */
/*   Updated: 2023/07/24 17:25:31 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_option(char **cmd, int *index)
{
	int	bslash_n;
	int	j;

	bslash_n = 1;
	while (cmd[*index] && ft_strncmp(cmd[*index], "-n", 2) == 0)
	{
		j = 2;
		while (cmd[*index][j] && cmd[*index][j] == 'n')
			j++;
		if (cmd[*index][j] && cmd[*index][j] != '\0')
			return (bslash_n);
		else if (*index == 1)
			bslash_n = 0;
		(*index)++;
	}
	return (bslash_n);
}

int	ft_echo(t_parser *parser)
{
	int			index;
	int			bslash_n;
	t_parser	*echo;

	echo = parser;
	index = 1;
	bslash_n = check_option(echo->cmd, &index);
	while (echo->cmd[index])
	{
		ft_putstr_fd(echo->cmd[index], STDOUT_FILENO);
		if (echo->cmd[index + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		index++;
	}
	if (bslash_n)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
