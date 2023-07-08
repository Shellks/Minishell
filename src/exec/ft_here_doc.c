/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:46:49 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/08 17:57:35 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minishell.h"

// void    child_heredoc(t_redir *re, int p_to_c[2], int c_to_p[2], int pipe[2])
// {
//     int     read_byte;
//     char    buf[100];

//     close(c_to_p[0]);
//     close(pipe[0]);
//     close(pipe[1]);
//     while (1)
// 	{
// 		write(1, "here_doc> ", 11);
//         read_byte = read(p_to_c[0], buf, sizeof(buf));
//         if (read_byte > 0)
//         {
//             if (ft_strncmp(buf, re->redirec, ft_strlen(re->redirec)) == 0)
//                 break ;
//             write(c_to_p[1], buf, read_byte);
//         }
//         else
//             break;
// 	}
//     close(p_to_c[0]);
//     close(c_to_p[1]);
//     close(p_to_c[1]);
// }

// void    parent_heredoc(t_redir *re, int p_to_c[2], int c_to_p[2], int pipe[2])
// {
//     int     read_byte;
//     int     read_from_child;
//     char    buf[100];

//     close(c_to_p[1]);
//     close(p_to_c[0]);
//     while (1)
// 	{
//         read_byte = read(STDIN_FILENO, buf, sizeof(buf));
//         if (read_byte > 0)
//         {
//             write(p_to_c[1], buf, read_byte);
//             read_from_child = read(c_to_p[0], buf, sizeof(buf));
//             write(pipe[1], buf, read_from_child);
//             if (ft_strncmp(buf, re->redirec, ft_strlen(re->redirec)) == 0)
//                 break ;
//         }
//         else
//             break ;
//     }
//     close(p_to_c[1]);
//     close(c_to_p[0]);
// }

// void	get_heredoc(t_data *data, t_redir *redir, t_exec *exec)
// {
//     int parent_to_child[2];
//     int child_to_parent[2];

//     if (exec->flag_in == 1)
//     {
//         exec->flag_in = 0;
//         close(exec->infile);
//     }
// 	if (pipe(parent_to_child) < 0 || pipe(child_to_parent) < 0)
// 		exit (false);
//     if (pipe(exec->here_doc) < 0)
//         exit (false);
//     exec->pid = fork ();
//     if (exec->pid == -1)
//         ft_free_exit(data, ERR_FORK, "Error with creating fork\n");
//     if (exec->pid == 0)
//         child_heredoc(redir, parent_to_child, child_to_parent, exec->here_doc);
//     else
//     {
//         parent_heredoc(redir, parent_to_child, child_to_parent, exec->here_doc);
//         printf("Coucou\n");
//         wait(NULL);
//     }
//     exec->flag_in = 2;
// }
