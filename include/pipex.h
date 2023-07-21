/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:53:15 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/20 14:30:45 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "../printf/ft_printf.h"

# define BUFFER_SIZE 5
# define ERR_ARGS 1
# define ERR_INFILE 2
# define ERR_OUTFILE 3
# define ERR_ENVP 4
# define ERR_SPLIT 5
# define ERR_PIPE 6
# define ERR_FORK 7
# define ERR_DUP 8
# define ERR_EXEC 9
# define ERR_MALLOC 10
# define ERR_DOC 11
# define ERR_CMD 127
# define CLOSE_FILE 1
# define CLOSE_ALL 2
# define CLOSE_END 3
# define FREE_PARENT 1
# define FREE_CHILD 2

typedef struct s_pipe
{
	int		infile;
	int		outfile;
	int		pipes[2];
	int		here_doc[2];
	int		status;
	int		exit_status;
	pid_t	pid;
	int		doc;
	char	**env_var;
	char	**cmd_args;
	int		pipe_num;
}	t_pipe;

void	pipex(t_pipe *p, char **argv, char **envp);
void	last_child(t_pipe *p, char **envp, char **argv, int i);
void	child_process(t_pipe *p, char **envp, char **argv, int i);
void	ft_close(t_pipe *p, int in_out, int pipe, int std);
void	ft_close_free(t_pipe *p, int close, int free, int error);
void	ft_free_child(t_pipe *p, int error);
void	ft_free_parent(t_pipe *p, int error);

#endif
