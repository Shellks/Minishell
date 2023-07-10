/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbernard <nicolasbernard@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:50:43 by nicolasbern       #+#    #+#             */
/*   Updated: 2023/07/10 10:17:11 by nicolasbern      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



int ft_dup_fd(t_parser *parser)
{
	if (parser->fd_input != NULL)
	{
		if (dup2(*(parser->fd_input), 0) == -1)
		{
			perror("ERR_DUP");
			if (close(*(parser->fd_input)) == -1)
				perror("ERR_CLOSE");
			return (EXIT_FAILURE);
		}
		if (*parser->fd_input != -1 && close(*parser->fd_input) == -1)
			perror("ERR_CLOSE");
	}
	if (parser->fd_output != NULL)
	{
		if (dup2(*(parser->fd_output), 1) == -1)
		{
			perror("ERR_DUP2");
			if (close(*(parser->fd_output)) == -1)
				perror("ERR_CLOSE");
			return (EXIT_FAILURE);
		}
		if (*parser->fd_output != -1 && close(*parser->fd_output) == -1)
			perror("ERR_CLOSE");
	}
	return (0);
}

int check_option(char **cmd, int *index)
{
    int bslash_n;
    int j;

    bslash_n = 1;
	while (cmd[*index] && ft_strncmp(cmd[*index], "-n", 2) == 0)
	{
		j = 2;
		while (cmd[*index][j] && cmd[*index][j] == 'n')
			j++;
		if (cmd[*index][j] && cmd[*index][j] != '\0')
			return (bslash_n);
		else if (*index == 1)
			bslash_n = 0;
		(*index)++;
	}
    return (bslash_n);
}


bool ft_echo(t_data *data)
{
    int index;
    int bslash_n;
    t_parser *echo;

    echo = data->parser;
    //TODO : redir le result de printf avec dup2
    echo->pid = fork();
    // if (echo->pid == -1)
    //     exit (EXIT_FAILURE);
    // if (ft_dup_fd(echo))
    //     exit(EXIT_FAILURE);
    index = 1;
    bslash_n = check_option(echo->cmd, &index);
    while (echo->cmd[index])
    {
        ft_putstr_fd(echo->cmd[index], 1);
        if (echo->cmd[index + 1])
			ft_putstr_fd(" ", 2);
        index++;
    }
    if (bslash_n)
        ft_putstr_fd("\n", 1);
    return (true);
}