/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:46:29 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/12 15:09:21 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Own library
# include "env.h"
# include "lexer.h"
# include "parser.h"
# include "exec.h"
# include "builtin.h"
//boolean
# include <stdbool.h>
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
//Library for waitpid
# include <sys/wait.h>

# define COLOR "\x1b[36;1m"
# define RESET "\x1b[0m"
# define BUFFER_SIZE 10
# define NONE 0
# define REDIR 1
# define BREAK -1
# define TRUE 0
# define FALSE 1
# define ERR_MALLOC 2
# define ERR_SYNTAX 3
# define ERR_FORK	4

extern int g_status;

typedef struct s_data
{
	t_env		*pwd;
	t_env		*old_pwd;
	t_env		*env;
	char		**path;
	char		*cmd_path;
	char		*input;
	int			flag;
	int			quote_error;
	int			count;
	t_lexer		*lexer;
	t_parser	*parser;
	int			pipe;
}			t_data;

//builtin=====
bool	ft_env(t_data *data);
bool 	ft_echo(t_data *data);
bool    ft_cd(t_data *data, char **tab);
void	get_pwd(t_data *data);
void	set_env(t_data *data, char **env);
//lexer fonction
bool	lexer(t_data *data);
bool	find_dollar(char *str);
int		count_node(t_lexer	*lexer);
void	print_lexer(t_lexer **lexer);
int		check_quote(t_data *data, int i);
int		build_token(int i, char *str, t_data *data);
int		get_anti_slash(int i, char *str, t_data *data);
int		get_word(t_data *data, char *str, int start, int stop);
int		get_word_in_quote(t_data *data, char *str, int start, int stop);
//expand fonction
int		expand(t_data *data, char *str, int i);
void	expand_status(t_data *data, char *str);
void	create_expand_digit(t_data *data, char *str);
int		expand_in_quote(t_data *data, char *str, int i);
bool	check_backslah_quote(t_data *data, char *str, int *i);
void	replace_false_expand_quote(t_data *data, t_lexer *end);
void	get_next_expand(t_data *data, char *str, char *tmp2, int i);
bool	check_space_env_content(t_data *data, t_env *env, t_lexer *src);
//parser fonction
bool	ft_parser(t_data *data);
void	ft_fusion(t_data *data);
void	del_node_space(t_data *data);
void	print_parser(t_parser **parser);
void	ft_print_syntax_error(char * word);
//built_in fonction
void    ft_exit(t_data *data);
bool    ft_unset(t_data *data, t_parser *parser);
bool    ft_export(t_data *data, t_parser *parser);
//exec fonction
void	get_heredoc(t_data *data, t_redir *redir, t_exec *exec);
bool    ft_set_redir(t_data *data, t_parser *parser, t_exec *exec);
char   *expand_here_doc(t_data *data, char *str, int i);
//fonction temporaire pour free
void	ft_free_env(t_data *data);
void	ft_free_loop(t_data *data);
void	ft_free_split(t_data *data);
void	ft_free_exit(t_data	*data, int	error, char *msg);
void	free_exit_env(t_data *data, char *name, char *content, int i);
//gnl
char	*get_next_line(int fd);
//fonction temporaire pour close
void    ft_close_here_doc(t_exec *exec, int *fd, int sign);

#endif
