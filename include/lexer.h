/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:33:37 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/05 13:23:26 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define PRINT_NULL					"(NULL)"
# define PRINT_PIPE					"PIPE"
# define PRINT_INFILE				"INFILE"
# define PRINT_HERE_DOC				"HERE_DOC"
# define PRINT_OUTFILE				"OUTFILE"
# define PRINT_OUTFILE_APPEND		"OUTFILE_APPEND"
# define PRINT_DELIMITER			"SPACE"
# define PRINT_WORD					"WORD"
# define PRINT_EXPAND				"EXPAND"

typedef enum e_token
{
	NULL,
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
	t_token			token;
	int				index;
	struct s_lexer	*previous;
	struct s_lexer	*next;
}			t_lexer;

t_lexer		*ft_lexer_last(t_lexer *lst);
int			ft_lexer_size(t_lexer *lst);
t_lexer		*ft_lexer_first(t_lexer *lst);
void		ft_lexer_clear(t_lexer **lst);
void		ft_lexer_delone(t_lexer *lst);
t_lexer		*ft_lexer_new(char *word, t_token token, int index);
void		ft_lexer_add_back(t_lexer **lst, t_lexer *new);
void		ft_lexer_add_front(t_lexer **lst, t_lexer *new);

#endif
