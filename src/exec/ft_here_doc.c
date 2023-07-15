/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:46:49 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/14 20:46:16 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void    child_heredoc_expand(t_data *data, t_exec *exec, t_redir *re, int pipe[2])
{
  char    *str;

  close(exec->here_doc[0]);
  close(exec->here_doc[1]);
  close(pipe[0]);
  while (1)
	{
    str = readline("> ");
    if (!str)
      break ;
    if (ft_strncmp(str, re->redirec, ft_strlen(re->redirec)) == 0)
      break ;
    str = expand_here_doc(data, str, ft_strlen(str));
    //ft_putstr_fd(str, pipe[1]);
    ft_putstr_fd("\n", pipe[1]);
    free (str);
	}
  free(str);
  close(pipe[1]);
}

static void    child_heredoc(t_exec *exec, t_redir *re, int pipe_connect[2])
{
  char    *str;

  close(exec->here_doc[0]);
  close(exec->here_doc[1]);
  close(pipe_connect[0]);
  while (1)
	{
    str = readline("> ");
    if (!str)
      break ;
    if (ft_strncmp(str, re->redirec, ft_strlen(re->redirec)) == 0)
      break ;
    //ft_putstr_fd(str, pipe_connect[1]);
    //ft_putstr_fd("\n", pipe_connect[1]);
    free (str);
	}
  free(str);
  close(pipe_connect[1]);
}

static void    parent_heredoc(t_redir *re, int pipe_connect[2], int pipe[2])
{
  char      *str;
  int       fd;

  close(pipe_connect[1]);
  fd = open(re->next->redirec, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  while (1)
	{
    str = get_next_line(pipe_connect[0]);
    if (!str)
      break ;
    if (ft_strncmp(str, re->redirec, ft_strlen(re->redirec)) == 0)
      break ;
    ft_putstr_fd(str, pipe[1]);
    //ft_putstr_fd(str, fd);
    free(str);
  }
  free(str);
  close(fd);
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
      if (redir->quote != NONE)
        child_heredoc(exec, redir, pipe_connect);
      else
        child_heredoc_expand(data, exec, redir, pipe_connect);
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
