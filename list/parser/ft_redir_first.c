#include "../../include/minishell.h"

t_redir	*ft_redir_first(t_redir *lst)
{
	if (!lst)
		return (0);
	while (lst->previous)
		lst = lst->previous;
	return (lst);
}