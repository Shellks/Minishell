/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:57:32 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/15 16:20:11 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_std_manager(int STDIN,int STDOUT)
{
	int	wait_all = 0;

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	while (wait_all != -1)
		wait_all = waitpid(-1, NULL, 0);
	dup2(STDIN, STDIN_FILENO);
	dup2(STDOUT, STDOUT_FILENO);
}

void	ft_dup_manager(t_data *data, t_exec *exec)
{
	if (exec->flag_in == 1)
		dup2(exec->infile, STDIN_FILENO);
	else if (exec->flag_in == 2)
	{
		exec->infile = open(data->here_doc_path->redirec, O_RDONLY);
		if (exec->infile < 0)
			ft_free_exit(data, ERR_OPEN, "Error opening file\n");
		dup2(exec->infile, 0);
		unlink(data->here_doc_path->redirec);
	}
	if (exec->flag_out == 1)
		dup2(exec->outfile, STDOUT_FILENO);
}

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
