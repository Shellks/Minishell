/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 08:10:20 by nibernar          #+#    #+#             */
/*   Updated: 2022/11/23 10:02:39 by nibernar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_len(unsigned int nbr)
{
	int	len;

	len = 0;
	while (nbr >= 10)
	{
		len++;
		nbr /= 10;
	}
	return (len + 1);
}

static char	*ft_itoa_bis(unsigned int nbr, char *dest, int i, unsigned int len)
{
	while (nbr >= 10)
	{
		dest[i--] = nbr % 10 + '0';
		nbr /= 10;
	}
	dest[i] = nbr % 10 + '0';
	dest[len] = '\0';
	return (dest);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	unsigned int	len;
	unsigned int	i;
	int				signe;
	char			*dest;

	if (n < 0)
		nbr = (unsigned int)(n * -1);
	else
		nbr = (unsigned int)(n);
	signe = 0;
	len = size_len(nbr);
	if (n < 0)
		signe = 1;
	i = 0;
	dest = (char *)malloc(sizeof(*dest) * (len + 1 + signe));
	if (!dest)
		return (0);
	if (n < 0)
	{
		dest[i] = '-';
		len++;
	}
	i = len -1;
	return (ft_itoa_bis(nbr, dest, i, len));
}
