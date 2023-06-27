/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:12:58 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/26 13:50:38 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	debug_token_1(int tokenType)
{
	switch (tokenType)
	{
		case 0:
		{
			dprintf(2, "token: %s\n", PRINT_NULL);
			break ;
		}
		case 1:
		{
			dprintf(2, "token: %s\n", PRINT_PIPE);
			break ;
		}
		case 2:
		{
			dprintf(2, "token: %s\n", PRINT_INFILE);
			break ;
		}
		default :
			break ;
	}
}

static void	debug_token_2(int tokenType)
{
	switch (tokenType)
	{
		case 3:
		{
			dprintf(2, "token: %s\n", PRINT_HERE_DOC);
			break ;
		}
		case 4:
		{
			dprintf(2, "token: %s\n", PRINT_OUTFILE);
			break ;
		}
		case 5:
		{
			dprintf(2, "token: %s\n", PRINT_OUTFILE_APPEND);
			break ;
		}
		case 6:
		{
			dprintf(2, "token: %s\n", PRINT_DELIMITER);
			break ;
		}
		case 7:
		{
			dprintf(2, "token: %s\n", PRINT_WORD);
			break ;
		}
		default :
			break ;
	}
}

static void	debug_token( int token_type )
{
	if (token_type >= 0 && token_type <= 2)
		debug_token_1(token_type);
	else
		debug_token_2(token_type);
}

void	print_lexer(t_lexer **lexer)
{
	t_lexer	*tmp;

	tmp = NULL;
	tmp = *lexer;
	while (tmp)
	{
		printf("char : |%s|\n", tmp->word);
		debug_token(tmp->token);
		printf("index : %d\n", tmp->index);
		dprintf(2, "\n\n");
		tmp = tmp->next;
	}
}
