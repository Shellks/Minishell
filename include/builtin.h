/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbernard <nicolasbernard@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 00:00:38 by nicolasbern       #+#    #+#             */
/*   Updated: 2023/07/07 00:05:02 by nicolasbern      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include <stdbool.h>

typedef struct s_echo
{
    int     i;
    int     j;
    int     len;
    int     flag;
    bool    backslash_n;
}               t_echo;

#endif