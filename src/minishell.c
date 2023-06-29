/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:08:57 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/29 18:51:01 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status;

void	create_chained_parsing(t_data *data, t_lexer *lexer, t_parser *lst, int i)
{
	int		len;
	char	*tmp;

	len = 0;
	lst->cmd = (char **)ft_calloc(sizeof(char *), i);
	if (!lst->cmd)
		ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
	while(lexer && len < i)
	{
		if (lexer->token != SPACE && lexer->token != WORD)
		{
			lst->redir->token = lexer->token;
			if (lexer->next->next)
			{
				lst->redir->redirec = ft_strdup(lexer->next->next->word);
				lexer = lexer->next->next;
				len += 2;
			}
			else
			{
				printf("syntax error near unexpected token `newline'\n");
				return ;
			}
		}
		else if (lexer->token == WORD)
		{
			tmp = ft_strdup(lexer->word);
			if (!tmp)
				ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
			lst->cmd[len] = ft_strjoin(lst->cmd[len], tmp);
			lexer = lexer->next->next;
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
	t_lexer		*tmp_lexer;
	t_parser	*tmp_parser;
	t_parser	*new;

	i = 0;
	tmp_lexer = ft_lexer_first(data->lexer);
	new = ft_parser_new();
	if (!new)
		ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
	ft_parser_add_back(&data->parser, new);
	tmp_parser = ft_parser_last(data->parser);
	if (tmp_lexer->token == PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return ;
	}
	i = count_node(tmp_lexer);
	tmp_lexer = ft_lexer_first(data->lexer);
		if (tmp_lexer->token != PIPE)
			create_chained_parsing(data, tmp_lexer, tmp_parser, i);
		if (tmp_lexer->token == PIPE && tmp_lexer->next)
		{
			new = ft_parser_new();
			if (!new)
				ft_free(data, ERR_MALLOC, "Malloc error\n", 2);
			ft_parser_add_back(&data->parser, new);
			i = count_node(tmp_lexer);
			tmp_parser = tmp_parser->next;
		}
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
		ft_parser(&data);
		free (data.input);
	}
	ft_env_clear(&data.env);
}
