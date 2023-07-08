/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:55:59 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/08 15:16:20 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


static bool	get_infile(t_redir *redir, t_exec *exec)
{
    if (!redir->redirec)
        return (false);
    if (exec->flag_in == 1)
    {
        exec->flag_in = 0;
        close(exec->infile);
    }
    exec->infile = open(redir->redirec, O_RDONLY);
    if (exec->infile < 0)
    {
		printf("no such file or directory: %s\n", redir->redirec);
        return (false);
    }
    printf("infile : %s  Add !\n", redir->redirec);
    exec->flag_in = 1;
    return (true);
}
static bool	get_outfile(t_redir *redir, t_exec *exec)
{
    if (!redir->redirec)
        return (false);
    if (exec->flag_out == 1)
    {
        exec->flag_out = 0;
        close(exec->outfile);
    }
    exec->outfile = open(redir->redirec, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (exec->outfile < 0)
    {
		printf("no such file or directory: %s\n", redir->redirec);
        return (false);
    }
    printf("outfile : %s   Add!\n", redir->redirec);
    exec->flag_out = 1;
    return (true);
}
// static bool	get_heredoc(t_redir *redir, t_exec *exec)
// {
//     char	*str;

// 	if (pipe(exec->here_doc) < 0)
// 		exit (false);
// 	while (1)
// 	{
// 		write(1, "here_doc> ", 11);
// 		str = get_next_line(STDIN_FILENO);
// 		if (str == NULL)
// 			exit (false);
// 		if (ft_strncmp(str, redir->redirec, ft_strlen(redir->redirec)) == 0 && 
// 		    ft_strlen(str) == ft_strlen(redir->redirec) +1)
// 		{
// 			free(str);
// 			break ;
// 		}
// 		write(exec->here_doc[1], str, ft_strlen(str));
// 		free(str);
// 	}
// }
static bool	get_append(t_redir *redir, t_exec *exec)
{
    if (!redir->redirec)
        return (false);
    if (exec->flag_out == 1)
    {
        exec->flag_out = 0;
        close(exec->outfile);
    }
    exec->outfile = open(redir->redirec, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (exec->outfile < 0)
    {
		printf("no such file or directory: %s\n", redir->redirec);
        return (false);
    }
    printf("append : %s  Add !\n", redir->redirec);
    exec->flag_out = 1;
    return (true);
}

static bool    set_redir_loop(t_exec *exec, t_redir *redir)
{
    // if (redir->token == HERE_DOC)
    // {
    //     if (get_heredoc(redir, exec) == false)
    //         return (false);
    // }
    if (redir->token == INFILE)
    {
        if (get_infile(redir, exec) == false)
            return (false);
    }
    else if (redir->token == OUTFILE)
    {
         if (get_outfile(redir, exec) == false)
            return (false);
    }
    else if (redir->token == OUTFILE_APPEND)
    {
        if (get_append(redir, exec) == false)
            return (false);
    }
    return (true);
}

bool    ft_set_redir(t_parser *parser, t_exec *exec)
{
    t_redir *tmp_redir;

    if (!parser->redir)
        return (false);
    tmp_redir = parser->redir;
    while (tmp_redir)
    {
        if (set_redir_loop(exec, tmp_redir) == false)
        {
            if (exec->flag_in == 1)
                close(exec->infile);
            if (exec->flag_out == 1)
                close(exec->outfile);
            return (false);
        }
        tmp_redir = tmp_redir->next;
    }
    if (exec->flag_in == 1)
        close(exec->infile);
    if (exec->flag_out == 1)
        close(exec->outfile);
    return (true);
}
