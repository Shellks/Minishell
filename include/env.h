/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 09:13:19 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/08 10:44:31 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*name;
	char			*content;
	int				flag;
	struct s_env	*previous;
	struct s_env	*next;
}				t_env;

t_env	*ft_env_last(t_env *lst);
int		ft_env_size(t_env *lst);
t_env	*ft_env_first(t_env *lst);
void	ft_env_clear(t_env **lst);
void	ft_env_delone(t_env *lst);
t_env	*ft_env_new(char *name, char *content);
void	ft_env_add_back(t_env **lst, t_env *new);
void	ft_env_add_front(t_env **lst, t_env *new);

#endif