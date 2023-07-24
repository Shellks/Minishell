/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:12:46 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/24 14:56:10 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_split(char	**tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	ft_print_error(char *str1, char *str2, char *str3, char *str4)
{
	if (str1)
		ft_putstr_fd(str1, 2);
	if (str2)
		ft_putstr_fd(str2, 2);
	if (str3)
		ft_putstr_fd(str3, 2);
	if (str4)
		ft_putstr_fd(str4, 2);
}
