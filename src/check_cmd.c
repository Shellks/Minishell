/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:35:41 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/19 18:17:32 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int is_builtin_command(char *cmd) 
// {
// 	char	**builtin_command;
// 	char 	*str_builtin;
// 	int		i;
// 	int		len;

// 	str_builtin = (char *)malloc(sizeof(char) * 93);
// 	if (!str_builtin)
// 		return (FALSE);
// 	str_builtin = "alias|history|source|.|type|jobs|fg|bg|kill|umask|exec|\
// 	readonly|set|shift|test|[|TRUE|FALSE";
// 	builtin_command = ft_split(str_builtin, '|');
// 	if (!builtin_command)
// 		return (FALSE);
// 	len = ft_strlen(cmd);
// 	i = -1;
// 	while(builtin_command[++i])
// 	{
// 		if (ft_strncmp(builtin_command[i], cmd, len) == 0)
// 		{
// 			printf("minishell: %s is a builtin command\n", cmd);
// 			return (TRUE);
// 		}
// 	}
// 	return (FALSE);
// }

// int	get_cmd(t_data *data, char *cmd)
// {
// 	char	*temp;
// 	int		i;

// 	data->cmd_path = NULL;
// 	if (access(cmd, 0) == 0)
// 		return	(TRUE);
// 	if (cmd[0] == '/')
// 		return (TRUE);
// 	i = -1;
// 	while (data->path[++i])
// 	{
// 		temp = ft_strjoin(data->path[i], "/");
// 		if (temp == NULL)
// 			return (FALSE);
// 		data->cmd_path = ft_strjoin(temp, cmd);
// 		if (data->cmd_path == NULL)
// 			return(free(temp), FALSE);
// 		free (temp);
// 		if (access(data->cmd_path, 0) == 0)
// 			return (TRUE);
// 		free(data->cmd_path);
// 	}
// 	return (FALSE);
// }

// int	check_cmd(t_data *data, char *cmd)
// {	
// //	ft_lexer_last(data->lexer);
// //	printf("%s\n", data->lexer[1].word);
// 	// if (is_builtin_command(cmd) == TRUE)
// 	// 	return (FALSE);
// 	// if (ft_env_size(data->env) == 2)
// 	// 	return (FALSE);
// 	if (ft_strncmp(cmd, "cd", 2) == 0)
// 		return (TRUE);
// 	else if (ft_strncmp(cmd, "export", 6) == 0)
// 		return (TRUE);
// 	else if (ft_strncmp(cmd, "unset", 5) == 0)
// 		return (TRUE);
// 	else if (ft_strncmp(cmd, "exit", 5) == 0)
// 		return (TRUE);
// 	if (!data->path)
// 		return (FALSE);
// 	else
// 		if (get_cmd(data, cmd) == TRUE)
// 			return (TRUE);
// 	return (FALSE);
// }
