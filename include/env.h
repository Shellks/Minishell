/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 09:13:19 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/20 14:14:56 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef enum e_equals
{
	EQUALS,
	NOT_EQUALS,
}	t_equals;

typedef struct s_env
{
	t_equals		equals;
	char			*name;
	char			*content;
	struct s_env	*previous;
	struct s_env	*next;
}				t_env;

t_env	*ft_env_last(t_env *lst);
int		ft_env_size(t_env *lst);
t_env	*ft_env_first(t_env *lst);
void	ft_env_clear(t_env **lst);
void	ft_env_delone(t_env *lst);
void	ft_env_add_back(t_env **lst, t_env *new);
void	ft_env_add_front(t_env **lst, t_env *new);
t_env	*ft_env_new(char *name, char *content, t_equals equals);

#endif