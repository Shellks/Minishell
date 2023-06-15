/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:33:37 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/14 18:10:19 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum	s_token
{
	PIPE,
	INFILE,
	HERE_DOC,
	OUTFILE,
	OUTFILE_APPEND,
}				e_token;

typedef struct s_lexer
{
	char			*word;
	e_token			token;
	int				index;
	struct s_lexer	*previous;
	struct s_lexer	*next;
}				t_lexer;

t_lexer		*ft_lexer_last(t_lexer *lst);
int			ft_lexer_size(t_lexer *lst);
t_lexer		*ft_lexer_first(t_lexer *lst);
void		ft_lexer_clear(t_lexer **lst);
void		ft_lexer_delone(t_lexer *lst);
t_lexer		*ft_lexer_new(char *word, e_token token, int index);
void		ft_lexer_add_back(t_lexer **lst, t_lexer *new);
void		ft_lexer_add_front(t_lexer **lst, t_lexer *new);

# endif