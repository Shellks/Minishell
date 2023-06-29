/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:05:19 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/29 18:51:18 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_redir
{
	char			*redirec;
	int				token;
	struct s_redir	*next;
}			t_redir;

typedef struct s_parser
{
	char			**cmd;
	t_redir			*redir;
	struct s_parser	*next;
}			t_parser;


t_parser	*ft_parser_new();
int			ft_parser_size(t_parser *lst);
t_parser	*ft_parser_last(t_parser *lst);
void		ft_parser_clear(t_parser **lst);
void		ft_parser_delone(t_parser *lst);
void		ft_parser_clear(t_parser **lst);
void		ft_parser_add_back(t_parser **lst, t_parser *new);

#endif