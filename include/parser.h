/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:05:19 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/03 18:07:32 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_redir
{
	char			*redirec;
	t_token			token;
	struct s_redir	*next;
	struct s_redir	*previous;
}			t_redir;

typedef struct s_parser
{
	char			**cmd;
	t_redir			*redir;
	struct s_parser	*next;
}			t_parser;

t_redir		*ft_redir_new();
t_parser	*ft_parser_new();
t_redir		*ft_redir_last(t_redir *lst);
t_redir		*ft_redir_first(t_redir *lst);
int			ft_parser_size(t_parser *lst);
t_parser	*ft_parser_last(t_parser *lst);
void		ft_parser_clear(t_parser **lst);
void		ft_parser_delone(t_parser *lst);
void		ft_parser_clear(t_parser **lst);
void		ft_parser_add_back(t_parser **lst, t_parser *new);
void		ft_redir_add_back(t_redir **lst, t_redir *new);

#endif