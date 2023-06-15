/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:57:05 by nibernar          #+#    #+#             */
/*   Updated: 2022/11/23 10:05:34 by nibernar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t			dest_len;
	size_t			src_len;
	size_t			i;

	if ((!dest || !src) && n == 0)
		return (0);
	i = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (dest_len < n -1 && (n != 0))
	{
		while (src[i] != '\0' && (dest_len + i < n - 1))
		{
			dest[dest_len + i] = src[i];
			i++;
		}
	}
	dest[dest_len + i] = '\0';
	if (dest_len > n)
		dest_len = n;
	return (dest_len + src_len);
}
