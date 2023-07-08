/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:41:35 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/08 15:50:54 by acarlott         ###   ########lyon.fr   */
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

typedef struct s_exec
{
    int     flag_in;
    int     flag_out;
    int     infile;
    int     outfile;
    int     here_doc[2];
    int     pid;

}   t_exec;

#endif