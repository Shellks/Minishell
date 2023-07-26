/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:15:36 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/26 18:16:58 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	unset_loop(t_data *data, t_env *env, t_parser *parser, int i)
{
	while (env)
	{
		if (ft_strncmp(parser->cmd[i], env->name, ft_strlen(env->name)) == 0)
		{
			if (!env->previous)
				data->env = data->env->next;
			ft_env_delone(env);
			break ;
		}
		else
			env = env->next;
	}
}

static bool	ft_check_unset(t_parser *parser, int i)
{
	if (parser->cmd[i][0] == '-' && parser->cmd[i][1])
	{
		ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
		ft_putstr_fd(parser->cmd[i], STDERR_FILENO);
		ft_putstr_fd("': invalid option\n", STDERR_FILENO);
		g_status = 2;
		return (false);
	}
	else if (is_valid_char(parser->cmd[i]) == false)
	{
		ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
		ft_putstr_fd(parser->cmd[i], STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		g_status = 1;
		return (false);
	}
	return (true);
}

void	ft_unset(t_data *data, t_parser *parser)
{
	t_env		*tmp_env;
	t_parser	*tmp_parser;
	int			i;

	tmp_env = data->env;
	tmp_parser = parser;
	if (!tmp_parser->cmd[1])
	{
		g_status = 0;
		return ;
	}
	if (!tmp_env)
	{
		g_status = 1;
		return ;
	}
	i = 0;
	while (tmp_parser->cmd[++i])
	{
		if (ft_check_unset(tmp_parser, i) == false)
			continue ;
		tmp_env = data->env;
		unset_loop(data, tmp_env, tmp_parser, i);
	}
	if (g_status == 1 || g_status == 2)
		return ;
	g_status = 0;
	return ;
}
