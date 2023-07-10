/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbernard <nicolasbernard@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:35:27 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/09 20:57:37 by nicolasbern      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*uns1;
	unsigned char	*uns2;

	i = 0;
	uns1 = ((unsigned char *) s1);
	uns2 = ((unsigned char *) s2);
	while ((uns1[i] != '\0' || uns2[i] != '\0') && i < n)
	{
		if (uns1[i] != uns2[i])
			return (uns1[i] - uns2[i]);
		i++;
	}
	//printf("s1 = |%s|    s2 = |%s|\n", s1, s2);
	return (0);
}
