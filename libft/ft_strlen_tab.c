/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbernard <nicolasbernard@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 20:08:18 by nicolasbern       #+#    #+#             */
/*   Updated: 2023/07/09 20:12:04 by nicolasbern      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strlen_tab(char **tab)
{
    int len;

    len = 0;
    while(tab[len])
        len++;
    return (len);
}