/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:46:29 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/21 14:35:23 by nibernar         ###   ########.fr       */
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
# include <limits.h>
//Libft
# include "../libft/libft.h"
//Library for environment
# include <readline/readline.h>
# include <readline/history.h>
//boolean
# include <stdbool.h>


# define GREEN "\x1b[36;1m"
# define RESET "\x1b[0m"
# define TRUE 0
# define FALSE 1
# define ERR_MALLOC 2
# define ERR_SYNTAX 3


typedef struct s_data
{
	t_env	*pwd;
	t_env	*old_pwd;
	t_env	*env;
	char	**path;
	char	*cmd_path;
	char	*input;
	int		quote_error;
	int		index;
	t_lexer	*lexer;
	int		pipe;
}			t_data;

void	get_pwd(t_data *data);
void	ft_fusion(t_data *data);
void	ft_free_split(t_data *data);
int		check_quote(t_data *data, int i);
void	set_env(t_data *data, char **env);
void	ft_free(t_data	*data, int	error, char *msg, int nb);
void	parsing(t_data	*data, char **argv, char **envp);
void	lexer(t_data *data);
int		build_token(int i, char *str, t_data *data);
void	print_lexer(t_lexer **lexer);
void	expand(t_data *data, char *str);

#endif
