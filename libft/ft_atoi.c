/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:30:32 by nibernar          #+#    #+#             */
/*   Updated: 2022/11/23 10:01:50 by nibernar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(const int c)
{
	return (c == '\n' || c == '\r' || c == '\v' || c == '\t' \
			|| c == '\f' || c == ' ');
}

int	ft_atoi(const char *str)
{
	int			i;
	int			negatif;
	long long	result;

	i = 0;
	negatif = 0;
	result = 0;
	while (str[i] != '\0' && (ft_isspace((const int)str[i])))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negatif = 1;
		i++;
	}
	while (str[i] && (ft_isdigit((int)str[i])))
	{
		if (ft_isdigit((int)str[i]))
			result = result * 10 + (str[i] - '0');
		i++;
	}
	if (negatif)
		result = result * -1;
	return ((int) result);
}
