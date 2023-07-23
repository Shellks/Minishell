/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 09:52:17 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/23 18:56:40 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_error(char *str1, char *str2, char *str3, char *str4)
{
	if (str1)
		ft_putstr_fd(str1, 2);
	if (str2)
		ft_putstr_fd(str2, 2);
	if (str3)
		ft_putstr_fd(str3, 2);
	if (str4)
		ft_putstr_fd(str4, 2);
}

void	ft_free_split(char	**tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_exit_env(t_data *data, char *name, char *content, int i)
{
	if (i == 1)
		free (name);
	if (i == 2)
	{
		free(name);
		free(content);
	}
	ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
}

void	ft_exit_minishell(t_data *data, t_exec *exec, int sign)
{
	if (sign == IS_PIPE)
		ft_close_all(data, exec, IS_PIPE);
	else if (sign == IS_NOT_PIPE)
		ft_close_all(data, exec, IS_NOT_PIPE);
	ft_free_exit(data, g_status, NULL);
}

void	ft_free_exit(t_data *data, int error, char *msg)
{
	if (data->input)
		free(data->input);
	if (data->path)
		ft_free_split(data->path);
	if (data->env)
		ft_env_clear(&data->env);
	if (data->lexer)
		ft_lexer_clear(&data->lexer);
	if (data->parser)
		ft_parser_clear(&data->parser);
	if (msg)
		printf("%s\n", msg);
	exit (error);
}

void	ft_free_env(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->path)
		ft_free_split(data->path);
	if (data->env)
		ft_env_clear(&data->env);
	if (data->lexer)
		ft_lexer_clear(&data->lexer);
	if (data->parser)
		ft_parser_clear(&data->parser);
}

void	ft_free_loop(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->lexer)
		ft_lexer_clear(&data->lexer);
	if (data->parser)
		ft_parser_clear(&data->parser);
}
