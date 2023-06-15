/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:53:34 by nibernar          #+#    #+#             */
/*   Updated: 2022/11/23 10:02:02 by nibernar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t n)
{
	void	*memstr;

	memstr = (void *)malloc(count * n);
	if (!memstr)
		return (0);
	ft_bzero(memstr, count * n);
	return (memstr);
}
