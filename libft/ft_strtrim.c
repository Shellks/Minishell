/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:23:48 by nibernar          #+#    #+#             */
/*   Updated: 2022/11/23 10:07:28 by nibernar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	to_find(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if (!s1)
		return (0);
	while (to_find(s1[i], set))
		i++;
	j = ft_strlen((char *)s1) - 1;
	while (s1[i] && to_find(s1[j], set))
		j--;
	str = (char *)malloc(sizeof(char) * (j - i + 1) + 1);
	if (!str)
		return (0);
	while (i <= j)
		str[k++] = s1[i++];
	str[k] = '\0';
	return (str);
}
