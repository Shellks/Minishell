/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 22:05:11 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/20 16:43:44 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_status_heredoc(t_data *data, char *str, int j, char *err_code)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strndup(str, j);
	if (!tmp1)
		free_exit_env(data, str, NULL, 1);
	tmp2 = ft_strjoin(tmp1, err_code);
	if (!tmp2)
	{
		free(err_code);
		free_exit_env(data, str, tmp1, 2);
	}
	free(tmp1);
	free(err_code);
	tmp1 = ft_strdup(&str[j + 2]);
	if (!tmp1)
		free_exit_env(data, tmp2, str, 2);
	free(str);
	str = ft_strjoin(tmp2, tmp1);
	if (!str)
		free_exit_env(data, tmp2, tmp1, 2);
	free(tmp1);
	free(tmp2);
	return (str);
}

char	*expand_digit_heredoc(t_data *data, char *str, int j)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strndup(str, j);
	if (!tmp1)
		free_exit_env(data, str, NULL, 1);
	tmp2 = ft_strdup(&str[j + 2]);
	if (!tmp1)
		free_exit_env(data, tmp2, str, 2);
	free(str);
	str = ft_strjoin(tmp1, tmp2);
	if (!str)
		free_exit_env(data, tmp1, tmp2, 2);
	free(tmp1);
	free(tmp2);
	return (str);
}
