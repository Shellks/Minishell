/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:12:58 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/06 16:15:49 by acarlott         ###   ########lyon.fr   */
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

void	print_parser(t_parser **parser)
{
	t_parser *tmp = *parser;
	t_redir	*tmp_redir;
	int	len;
	int	i;

	len = 0;
    while (tmp)
    {
        printf("\nRedirections[%d]:\n\n", len);
        tmp_redir = tmp->redir;
        while (tmp_redir)
        {
            debug_token(tmp_redir->token);
            printf("word-token : |%s|\n", tmp_redir->redirec);
			if (tmp_redir->next)
				printf("---\n");
            tmp_redir = tmp_redir->next;
        }
        
        printf("___________________\n\n");
        printf("Command[%d]:\n\n", len);
        i = 0;
        while (tmp->cmd[i])
        {
            printf("char[%d] : |%s|\n", i, tmp->cmd[i]);
            i++;
        }
        
        printf("___________________\n");
        
        tmp = tmp->next;
		len++;
    }
}