/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:31:30 by nibernar          #+#    #+#             */
/*   Updated: 2022/11/23 10:06:13 by nibernar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	if (ft_strlen(to_find) == 0)
		return ((char *) str);
	i = 0;
	while (i < n && str[i])
	{
		j = 0;
		while (to_find[j] && to_find[j] == str[i + j] && (n > i + j))
			j++;
		if (to_find[j] == '\0')
			return ((char *) str + i);
		i++;
	}
	return (0);
}
