/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:57:32 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/24 19:42:29 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_relative_path(t_data *data, t_parser *parse)
{
	char	*temp;
	char	*cmd;

	data->i = -1;
	while (data->path && data->path[++data->i])
	{
		temp = ft_strjoin(data->path[data->i], "/");
		if (!temp)
		{
			ft_putstr_fd("Malloc error\n", 2);
			ft_free_exit(data, ERR_MALLOC, NULL);
		}
		cmd = ft_strjoin(temp, parse->cmd[0]);
		if (!cmd)
		{
			ft_putstr_fd("Malloc error\n", 2);
			free_exit_env(data, temp, NULL, 1);
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
	ft_print_fd(parse->cmd[0], ": no such file or directory\n");
	ft_close(STDIN_FILENO, STDOUT_FILENO, -1);
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
		ft_print_fd(parse->cmd[0], ": no such file or directory\n");
		ft_close(STDIN_FILENO, STDOUT_FILENO, -1);
		ft_free_exit(data, 127, NULL);
	}
	if (S_ISDIR(path.st_mode))
	{
		ft_print_fd(parse->cmd[0], ": is a directory\n");
		ft_close(STDIN_FILENO, STDOUT_FILENO, -1);
		ft_free_exit(data, 126, NULL);
	}
	if (!access(parse->cmd[0], X_OK))
		return (parse->cmd[0]);
	ft_print_fd(parse->cmd[0], ": permission denied\n");
	ft_close(STDIN_FILENO, STDOUT_FILENO, -1);
	ft_free_exit(data, 126, NULL);
	return (NULL);
}

char	*ft_get_cmd(t_data *data, t_parser *parse)
{
	char	*cmd;

	get_path(data);
	cmd = is_absolute_path(data, parse);
	if (!cmd)
		cmd = is_relative_path(data, parse);
	return (cmd);
}
