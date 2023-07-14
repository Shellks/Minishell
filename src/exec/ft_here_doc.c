/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:46:49 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/11 17:55:23 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    child_heredoc(t_exec *exec, t_redir *re, int pipe_connect[2])
{
  char    *str;

  while (1)
	{
    str = readline("here_doc> ");
    if (!str)
      break ;
    if (ft_strncmp(str, re->redirec, ft_strlen(re->redirec)) == 0)
      break ;
    write(pipe_connect[1], str, ft_strlen(str));
    free (str);
	}
  ft_close_here_doc(exec, 0, 1);
  close(pipe_connect[1]);
  close(pipe_connect[0]);
}

void    parent_heredoc(t_redir *re, int pipe_connect[2], int pipe[2])
{
  char      buf[100];
  ssize_t   read_byte;
  char      *str;
  //int       fd;

  ft_memset(buf, 0, 100);
  close(pipe_connect[1]);
  //fd = open(re->next->redirec, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  while (1)
	{
    read_byte = read(pipe_connect[0], buf, sizeof(buf));
    if (read_byte > 0)
    {
      buf[read_byte] = '\0';
      str = ft_strnstr(buf, re->redirec, read_byte);
        if (!str)
        {
          write(pipe[1], buf, read_byte);
          //write(fd, buf, read_byte);
        }
        else
          break ;
    }
    else
      break ;
  }
  //close(fd);
  close(pipe_connect[0]);
}

void	get_heredoc(t_data *data, t_redir *redir, t_exec *exec)
{
    int pipe_connect[2];

    if (exec->flag_in == 1)
    {
        exec->flag_in = 0;
        close(exec->infile);
    }
    if (pipe(exec->here_doc) < 0 || pipe(pipe_connect) < 0)
		  ft_free_exit(data, ERR_FORK, "minishell: error with creating pipe\n");
    exec->pid = fork ();
    if (exec->pid == -1)
        ft_free_exit(data, ERR_FORK, "Error with creating fork\n");
    if (exec->pid == 0)
    {
      child_heredoc(exec, redir, pipe_connect);
      printf("Child process ending !\n");
      ft_free_exit(data, 0, NULL);
    }
    else
    {
        parent_heredoc(redir, pipe_connect, exec->here_doc);
        wait(NULL);
    }
    printf("Here_doc created !\n");
    exec->flag_in = 2;
}
