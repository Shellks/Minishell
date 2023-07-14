/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:57:32 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/13 15:48:32 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	ft_free_child(t_pipe *p, int error)
// {
// 	int	i;

// 	i = -1;
// 	while (p->env_var[++i])
// 		free(p->env_var[i]);
// 	free(p->env_var);
// 	i = -1;
// 	while (p->cmd_args[++i])
// 		free(p->cmd_args[i]);
// 	free(p->cmd_args);
// 	exit(error);
// }

// void	ft_free_parent(t_pipe *p, int error)
// {
// 	int	i;

// 	i = -1;
// 	while (p->env_var[++i])
// 		free(p->env_var[i]);
// 	free(p->env_var);
// 	exit(error);
// }

// void	ft_close(t_pipe *p, int in_out, int pipe, int std)
// {
// 	if (in_out == 1)
// 	{
// 		if (p->doc == 0 && p->infile != -1)
// 			close(p->infile);
// 		close(p->outfile);
// 	}
// 	if (pipe == 1)
// 	{
// 		close(p->pipes[0]);
// 		close(p->pipes[1]);
// 	}
// 	if (std == 1)
// 	{
// 		close(STDIN_FILENO);
// 		close(STDOUT_FILENO);
// 	}
// 	if (p->doc == 1)
// 		close(p->here_doc[0]);
// }

// void	ft_close_free(t_pipe *p, int close, int free, int error)
// {
// 	if (close == CLOSE_FILE)
// 		ft_close(p, 1, 0, 1);
// 	if (close == CLOSE_ALL)
// 		ft_close(p, 1, 1, 1);
// 	if (close == CLOSE_END)
// 		ft_close(p, 1, 0, 0);
// 	if (free == FREE_PARENT)
// 		ft_free_parent(p, error);
// 	if (free == FREE_CHILD)
// 		ft_free_child(p, error);
// }
