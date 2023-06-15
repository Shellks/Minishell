/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:03:16 by nibernar          #+#    #+#             */
/*   Updated: 2023/05/29 16:30:59 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

int	main(void)
{
	struct timeval tv;
    struct tm *timeinfo;


	
	gettimeofday(&tv, NULL);
	printf("date d'aujourd'hui en sec: %ld  en milisec: %ld\n", tv.tv_sec, tv.tv_usec);
	time_t seconds = tv.tv_sec;
    timeinfo = localtime(&seconds);
    printf("Date et heure locale : %s", asctime(timeinfo));
	return (0);	
}
