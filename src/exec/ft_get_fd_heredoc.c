/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_fd_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:49:09 by acarlott          #+#    #+#             */
/*   Updated: 2023/07/14 18:55:29 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char *get_here_doc_name(void)
{
    struct stat   path;
    char          *name;
    char          *tmp;
    int           i;

    i = 0;
    while (1)
    {
        tmp = ft_itoa(i);
        if (!tmp)
            return (NULL);
        name = ft_strjoin("/var/tmp/heredoc", tmp);
        if (!name)
            return (free(tmp), NULL);
        free(tmp);
        if (!stat(name, &path))
        {
            free(name);
            i++;
        }
        else
            break ;
    }
    return (name);
}
void get_here_doc_fd(t_data *data, t_redir *redir, int *fd)
{
    char    *name;

    name = get_here_doc_name();
    if (!name)
        ft_free_exit(data, ERR_MALLOC, "Malloc error\n");
    free(redir->redirec);
    redir->redirec = name;
    data->here_doc_path = redir;
    *fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (*fd < 0)
        ft_free_exit(data, ERR_OPEN, "Error opening temporary file\n");
}
