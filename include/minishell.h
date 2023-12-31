/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:46:29 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/28 12:29:46 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Own library
# include "env.h"
# include "lexer.h"
# include "parser.h"
# include "exec.h"
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
//signal
# include <signal.h>

# define COLOR "\001\x1b[36;1m\002"
# define RESET "\001\x1b[0m\002"
# define BUFFER_SIZE 10
# define NONE 0
# define REDIR 1
# define BREAK -1
# define TRUE 0
# define FALSE 1
# define ERR_MALLOC 2
# define ERR_SYNTAX 3

extern int	g_status;

typedef struct s_data
{
	t_env		*pwd;
	t_env		*old_pwd;
	t_env		*env;
	char		**path;
	char		*cmd_path;
	char		*input;
	char		*temp;
	int			flag;
	int			quote_error;
	int			count;
	t_lexer		*lexer;
	t_parser	*parser;
	t_redir		*here_doc_path;
	int			pipe;
	int			i;
}			t_data;

t_data	*ft_get_data(t_data *data);
//env fonction
void	create_usr_env(t_data *data);
void	create_shlvl(t_data *data);
void	create_pwd(t_data *data);
void	create_old_pwd(t_data *data);
void	get_path(t_data *data);
//builtin=====
bool	ft_built_in_process(t_data *data, t_exec *exec);
bool	ft_env(t_data *data);
int		ft_echo(t_parser *parser);
int		ft_dup_fd(t_parser *parser);
int		ft_cd(t_data *data, char **tab);
void	get_pwd(t_data *data);
void	set_env(t_data *data, char **env);
void	ft_pwd(void);
void	ft_exit(t_data *data, t_parser *parser, t_exec *exec);
int		ft_unset(t_data *data, t_parser *parser);
//builtin_export
bool	is_valid_char(char *name);
void	ft_print_export_sort(t_data *data);
void	ft_export(t_data *data, t_parser *parser);
t_env	*create_empty_env(t_data *data, char *name);
bool	ft_check_export_exist(t_data *data, char *parse, int end);
bool	export_join_content(t_data *data, char *parse, int end);
//lexer fonction
bool	lexer(t_data *data);
bool	find_dollar(char *str);
int		count_node(t_lexer	*lexer);
void	print_lexer(t_lexer **lexer);
int		check_quote(t_data *data, int i);
int		build_token(int i, char *str, t_data *data);
int		get_anti_slash(int i, char *str, t_data *data);
int		get_word(t_data *d, char *str, int start, int stop);
int		get_word_in_quote(t_data *d, char *s, int start, int stop);
//expand fonction
int		expand(t_data *data, char *str, int i);
void	expand_status(t_data *data, char *str);
void	create_expand_digit(t_data *data, char *str);
int		expand_in_quote(t_data *data, char *str, int i);
bool	check_backslah_quote(t_data *data, char *str, int *i);
void	replace_false_expand_quote(t_data *data, t_lexer *end);
void	get_next_expand(t_data *data, char *str, char *tmp2, int i);
bool	check_space_env_content(t_data *data, t_env *env, t_lexer *src);
void	child_heredoc_expand(t_data *data, t_redir *re, int pipe[2]);
//parser fonction
bool	ft_parser(t_data *data);
void	ft_fusion(t_data *data);
void	del_node_space(t_data *data);
void	print_parser(t_parser **parser);
void	ft_print_syntax_error(char *word);
//exec fonction
char	**get_env_tab(t_data *data);
int		is_builtin(t_data *data, t_parser *parse, t_exec *exec);
void	exec_simple_cmd(t_data *data, t_exec *exec);
void	pipex(t_data *data, t_exec *exec);
void	ft_std_manager(t_data *data, int STDIN, int STDOUT);
char	*expand_here_doc(t_data *data, char *str);
char	*ft_get_cmd(t_data *data, t_parser *parse, t_exec *exec);
void	ft_dup_manager(t_data *data, t_exec *exec);
void	ft_dup(t_data *data, int fd1, int fd2);
char	*expand_digit_heredoc(t_data *data, char *str, int j);
char	*replace_false_heredoc_expand(t_data *data, char *str, int *j);
char	*expand_status_heredoc(t_data *data, char *str, int j, char *err_code);
void	get_here_doc_fd(t_data *data, t_redir *redir, int *fd);
void	last_child(t_data *data, t_exec *exec, t_parser *parse);
void	get_heredoc(t_data *data, t_redir *redir, t_exec *exec);
void	child_process(t_data *data, t_exec *exec, t_parser *parse);
void	ft_set_redir(t_data *data, t_parser *parser, t_exec *exec);
void	ft_redir_error(t_redir *redir, t_exec *exec);
//Signal fonction
void	ft_ctrl_c(int signum);
void	ft_ctrl_c_exec(int signum);
void	ft_ctrl_c_heredoc(int signum);
//fonction temporaire pour free
void	ft_free_env(t_data *data);
void	ft_free_loop(t_data *data);
void	ft_free_split(char **tab);
void	ft_free_exit(t_data *data, int error, char *msg);
void	ft_child_exit(t_data *data, t_exec *exec, int sign);
void	free_exit_env(t_data *data, char *name, char *content, int i);
//gnl
char	*get_next_line(int fd);
//fonction temporaire pour close
void	ft_close(int fd1, int fd2, int fd3);
void	ft_close_all(t_data *data, t_exec *exec, int sign);
//fonction temporaire
void	ft_print_exit_error(char *cmd);
void	ft_print_export_error(char *word);
void	ft_print_error(char *str1, char *str2, char *str3, char *str4);
void	ft_print_fd(char *cmd, char *msg);
void	ft_print_fds(char *cmd, char *msg);
void	ft_exit_execve_fail(t_data *data, t_exec *exec, char *cmd, char **tab);

#endif
