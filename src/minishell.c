/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:08:57 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/30 14:16:45 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status;

void	del_node_space(t_data *data)
{
	t_lexer	*tmp;

	tmp = ft_lexer_first(data->lexer);
	while (tmp)
	{
		if (tmp->token == 6)
			ft_lexer_delone(tmp);
		tmp = tmp->next;
	}
}
// egfault ici !
void	create_chained_parsing(t_data *data, t_lexer *lexer, t_parser *lst, int i)
{
	int		len;
	char	*tmp;
	t_redir	*tmp_redir;

	tmp_redir = ft_redir_new();
	if (!tmp_redir)
		ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
	len = 0;
	lst->cmd = (char **)ft_calloc(sizeof(char *), i);
	if (!lst->cmd)
		ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
	while(lexer && len < i)
	{
		if (lexer->token != WORD)
		{
			if (lexer->next)
			{
				lst->redir->redirec = ft_strdup(lexer->next->word);
				printf("tok == %s\n", lst->redir->redirec);
			}
			else
			{
				printf("syntax error near unexpected token `newline'\n");
				return ;
			}
			//lst->redir = lst->redir->next;
		}
		else
		{
			tmp = ft_strdup(lexer->word);
			if (!tmp)
				ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
			printf("LEN == %d\n", len);
			printf("TMP == %s\n", tmp);
			lst->cmd[len] = tmp;
		}
		lexer = lexer->next;
		len++;
	}
}

int		count_node(t_lexer	*lexer)
{
	int	i;

	i = 0;
	while(lexer && lexer->token != PIPE)
	{
		i++;
		lexer = lexer->next;
	}
	return (i);
}

void	ft_parser(t_data *data)
{
	int			i;
	t_lexer		*lexer;
	t_parser	*parser;
	t_parser	*new;

	data->parser = NULL;
	i = 0;
	del_node_space(data);
	lexer = ft_lexer_first(data->lexer);
	new = ft_parser_new();
	if (!new)
		ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
	ft_parser_add_back(&data->parser, new);
	parser = ft_parser_last(data->parser);
	if (lexer->token == PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return ;
	}
	i = count_node(lexer);
	lexer = ft_lexer_first(data->lexer);
		if (lexer->token != PIPE)
			create_chained_parsing(data, lexer, parser, i);
		if (lexer->token == PIPE && lexer->next)
		{
			new = ft_parser_new();
			if (!new)
				ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
			ft_parser_add_back(&data->parser, new);
			i = count_node(lexer);
		}
		parser = parser->next;
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_env	*tmp;

	g_status = 0;
	if (argc != 1)
	{
		//printf("error\n");
		return (0);
	}
	parsing(&data, argv, env);
	tmp = data.env;
	while (tmp)
	{
		printf("%s : %s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
	while (1)
	{
		data.input = readline(COLOR"Minishell > "RESET);
		if (!data.input)
		{
			printf("exit\n");
			ft_env_clear(&data.env);
			return (0);
		}
		add_history(data.input);
		lexer(&data);
		free (data.input);
	}
	ft_env_clear(&data.env);
}
