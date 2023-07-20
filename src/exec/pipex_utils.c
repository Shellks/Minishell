/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:57:32 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/20 17:36:36 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_relative_path(t_data *data, t_parser *parse)
{
	char	*temp;
	char	*cmd;
	int		i;

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
		if (access(cmd, X_OK) == 0)
			return (cmd);
		free (cmd);
	}
	return (NULL);
}

static char	*is_relative_path(t_data *data, t_parser *parse)
{
	char	*cmd;

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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(parse->cmd[0], 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		ft_free_exit(data, 127, NULL);
	}
	if (S_ISDIR(path.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(parse->cmd[0], 2);
		ft_putstr_fd(": is a directory\n", 2);
		ft_free_exit(data, 126, NULL);
	}
	if (!access(parse->cmd[0], X_OK))
		return (parse->cmd[0]);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(parse->cmd[0], 2);
	ft_putstr_fd(": permission denied\n", 2);
	ft_free_exit(data, 126, NULL);
	return (NULL);
}

char	*ft_get_cmd(t_data *data, t_parser *parse)
{
	char	*cmd;

	cmd = is_absolute_path(data, parse);
	if (!cmd)
		cmd = is_relative_path(data, parse);
	return (cmd);
}

void	ft_std_manager(int STDIN, int STDOUT)
{
	int	wait_all;

	wait_all = 0;
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	while (wait_all != -1)
		wait_all = waitpid(-1, NULL, 0);
	dup2(STDIN, STDIN_FILENO);
	dup2(STDOUT, STDOUT_FILENO);
	close(STDIN);
	close(STDOUT);
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
