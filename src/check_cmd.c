/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:35:41 by acarlott          #+#    #+#             */
/*   Updated: 2023/06/16 20:03:30 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_builtin_command(char *cmd) 
{
	char	**builtin_command;
	char 	*str_builtin;
	int		i;
	int		len;

	str_builtin = (char *)malloc(sizeof(char) * 93);
	if (!str_builtin)
		return (false);
	str_builtin = "alias|history|source|.|type|jobs|fg|bg|kill|umask|exec|\
	readonly|set|shift|test|[|true|false";
	builtin_command = ft_split(str_builtin, '|');
	if (!builtin_command)
		return (false);
	len = ft_strlen(cmd);
	i = -1;
	while(builtin_command[++i])
	{
		if (ft_strncmp(builtin_command[i], cmd, len) == 0)
		{
			printf("minishell: %s is a builtin command\n", cmd);
			return (true);
		}
	}
	return (false);
}

int	get_cmd(t_data *data, char *cmd)
{
	char	*temp;
	char	*cmd2;
	int		i;

	i = -1;
	if (access(cmd, 0) == 0)
		return	(true);
	if (cmd[0] == '/')
		return (true);
	while (data->path[++i])
	{
		temp = ft_strjoin(data->path[i], "/");
		if (temp == NULL)
			return (false);
		cmd2 = ft_strjoin(temp, cmd);
		if (cmd2 == NULL)
			return(free(temp), false);
		free (temp);
		if (access(cmd2, 0) == 0)
			return (true);
		free (cmd2);
	}
	return (false);
}

int	check_cmd(t_data *data, char *cmd)
{	
//	ft_lexer_last(data->lexer);
//	printf("%s\n", data->lexer[1].word);
	if (is_builtin_command(cmd) == true)
		return (false);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (true);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (true);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (true);
	if (!data->path)
		return (false);
	else
		if (get_cmd(data, cmd) == true)
			return (true);
	return (false);
}

int	build_cmd(int i, char *str, t_data *data)
{
	int	j;
	t_lexer *tmp;

	(void) data;
	j = 0;
	while (str[i + j] && str[i + j] != ' ')
		j++;
	printf("%d\n", j);
	tmp = ft_lexer_new(ft_strndup(&str[i], j), WORD, 0);
	if (tmp == 0)
		return (false);
	if (check_cmd(data, tmp->word) == false)
	{
		printf("minishell: command not found: %s\n", tmp->word);
		return (i + j);
	}
	ft_lexer_add_back(&data->lexer, tmp);
	printf("char : %s|\n", tmp->word);
	return (i + j);
}