/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:33:37 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/28 12:39:31 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_quote
{
	NONE,
	SINGLE,
	DOUBLE,
	SLASH,
}	t_quote;

typedef enum e_token
{
	NOTHING,
	PIPE,
	INFILE,
	HERE_DOC,
	OUTFILE,
	OUTFILE_APPEND,
	DELIMITER,
	WORD,
	EXPAND,
}	t_token;

typedef struct s_lexer
{
	char			*word;
	t_quote			quote;
	t_token			token;
	struct s_lexer	*previous;
	struct s_lexer	*next;
}	t_lexer;

t_lexer		*ft_lexer_last(t_lexer *lst);
int			ft_lexer_size(t_lexer *lst);
t_lexer		*ft_lexer_first(t_lexer *lst);
void		ft_lexer_clear(t_lexer **lst);
void		ft_lexer_delone(t_lexer *lst);
t_lexer		*ft_lexer_new(char *word, t_token token, t_quote quote);
void		ft_lexer_add_back(t_lexer **lst, t_lexer *new);
void		ft_lexer_add_front(t_lexer **lst, t_lexer *new);

#endif
