/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbernard <nicolasbernard@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:50:43 by nicolasbern       #+#    #+#             */
/*   Updated: 2023/07/07 00:41:22 by nicolasbern      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool    init_struct_echo(t_echo *echo, char **tab)
{
    int count;

    count = -1;
    echo->len = 0;
    while (tab[++count])
        echo->len++;
    echo->flag = 0;
    echo->i = 1;
    echo->j = 0;
    echo->backslash_n = false;
    if (echo->len == 1)
    {
        printf("\n");
        return (false);
    }
    return (true);
}

static void    printf_echo(t_echo *echo, char *str, int len, int i)
{
    i++;
    echo->flag = 1;
    if (len == i)
    {
        if (echo->backslash_n == false)
            printf("%s\n", str);
        else
            printf("%s", str);
        
    }
    else
       printf("%s ", str);
}

static bool    check_char_n(t_echo *echo, char **tab)
{
    int len;

    len = 1;
    while (tab[echo->i][len])
    {
        if (tab[echo->i][len] != 'n')
        {
            if (echo->flag == 0)
                printf_echo(echo, tab[echo->i], echo->len, echo->i);
            return (false);
        }
        len++;
    }
    return (true);
}

void	builtin_echo(char **tab)
{
    t_echo  echo;

    if (init_struct_echo(&echo, tab) == false)
        return ;
    while(tab[echo.i])
    {
        if (echo.flag == 1)
            printf_echo(&echo, tab[echo.i], echo.len, echo.i);
        else if (tab[echo.i][0] == '-')
        {
            if (tab[echo.i][1] == '\0')
                printf_echo(&echo, tab[echo.i], echo.len, echo.i);
            else if (check_char_n(&echo, tab) == true)
                echo.backslash_n = true;
        }
        else if (tab[echo.i][0] != '-' || \
                (tab[echo.i][0] != 'n' && (echo.flag == 0)))
            printf_echo(&echo, tab[echo.i], echo.len, echo.i);
        echo.i++; 
    }
}
