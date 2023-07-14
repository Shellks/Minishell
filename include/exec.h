/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:41:35 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/14 16:28:09 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

//wait
# include <sys/wait.h>
//open
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define START_CMD 1
# define END_CMD 2
# define ERR_ARGS 1
# define ERR_INFILE 2
# define ERR_OUTFILE 3
# define ERR_ENVP 4
# define ERR_SPLIT 5
# define ERR_PIPE 6
# define ERR_FORK 7
# define ERR_DUP 8
# define ERR_EXEC 9
# define ERR_DOC 10
# define ERR_OPEN 11
# define ERR_CMD 127
# define CLOSE_FILE 1
# define CLOSE_ALL 2
# define CLOSE_END 3
# define FREE_PARENT 1
# define FREE_CHILD 2

typedef struct s_exec
{
    int     flag_in;
    int     flag_out;
    int     infile;
    int     outfile;
    int		pipes[2];
    int		status;
	int		exit_status;
	pid_t	pid;
	int		doc;
    
}   t_exec;

void	ft_close(t_exec *exec, int in_out, int pipe, int std);
void	ft_close_free(t_exec *exec, int close, int free, int error);
void	ft_free_child(t_exec *exec, int error);
void	ft_free_parent(t_exec *exec, int error);

#endif
