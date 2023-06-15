/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:46:29 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/15 11:48:00 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "env.h"
# include "lexer.h"
//Malloc
# include <stdlib.h>
//Printf
# include <stdio.h>
//PATH limit
#include <limits.h>
//Libft
# include "../libft/libft.h"
//Library for environment
# include <readline/readline.h>
# include <readline/history.h>

# define TRUE 0
# define FALSE 1
# define ERR_MALLOC 2

typedef struct s_data
{
	t_env	*pwd;
	t_env	*old_pwd;
	t_env	*env;
	char	**path;
	char	*input;
}			t_data;

void	get_pwd(t_data *data);
void	ft_free_split(t_data *data);
void	set_env(t_data *data, char **env);
void	ft_free(t_data	*data, int	error, char *msg);
void	parsing(t_data	*data, char **argv, char **envp);

# endif
