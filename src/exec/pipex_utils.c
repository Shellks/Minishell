/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:57:32 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/19 12:05:37 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *get_relative_path(t_data *data, t_parser *parse)
{
	char		*temp;
	char		*cmd;
	int			i;

	i = -1;
	while (data->path && data->path[++i])
	{
		temp = ft_strjoin(data->path[i], "/");
		if (!temp)
		{
			ft_putstr_fd("Malloc error\n", 2);
			ft_free_exit(data, ERR_MALLOC, NULL);
		}
		cmd = ft_strjoin(temp, parse->cmd[0]);
		if (!cmd)
		{
			free (temp);
			ft_putstr_fd("Malloc error\n", 2);
			ft_free_exit(data, ERR_MALLOC, NULL);
		}
		free (temp);
		//dprintf(2, "cmd2 = %s\n", cmd2);
		if (access(cmd, X_OK) == 0)
			return (cmd);
		free (cmd);
	}
	return (NULL);
}

static char	*is_relative_path(t_data *data, t_parser *parse)
{
	char		*cmd;

	cmd = get_relative_path(data, parse);
	if (cmd)
		return (cmd);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(parse->cmd[0], 2);
	ft_putstr_fd(": no such file or directory\n", 2);
	ft_free_exit(data, 127, NULL);
	return (NULL);
}

static char	*is_absolute_path(t_data *data, t_parser *parse)
{
	struct stat	path;
	if (!ft_strchr(parse->cmd[0], '/'))
		return (NULL);
	if (stat(parse->cmd[0], &path))
	{
		//ft_close a mettre la
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(parse->cmd[0], 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		ft_free_exit(data, 127, NULL);
	}
	if (S_ISDIR(path.st_mode))
	{
		//ft_close a mettre la
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(parse->cmd[0], 2);
		ft_putstr_fd(": is a directory\n", 2);
		ft_free_exit(data, 126, NULL);
	}
	if (!access(parse->cmd[0], X_OK))
		return(parse->cmd[0]);
	//ft_close a mettre la
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(parse->cmd[0], 2);
	ft_putstr_fd(": permission denied\n", 2);
	ft_free_exit(data, 126, NULL);
	return (NULL);

}

char	*ft_get_cmd(t_data *data, t_parser *parse)
{
	char			*cmd;
	cmd = is_absolute_path(data, parse);
	if (!cmd)
		cmd = is_relative_path(data, parse);
	return (cmd);
}

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
	{
		dup2(exec->infile, STDIN_FILENO);
		close(exec->infile);
	}
	else if (exec->flag_in == 2)
	{
		exec->infile = open(data->here_doc_path->redirec, O_RDONLY);
		if (exec->infile < 0)
			ft_free_exit(data, ERR_OPEN, "Error opening file\n");
		dup2(exec->infile, 0);
		close(exec->infile);
		unlink(data->here_doc_path->redirec);
	}
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
