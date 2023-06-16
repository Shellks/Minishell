/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:08:57 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/16 20:01:43 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	debugToken( int tokenType )
{
	switch (tokenType)
	{
		case 0:
		{
			dprintf(2, "token: %s\n", PRINT_PIPE);
			break;
		}
		case 1:
		{
			dprintf(2, "token: %s\n", PRINT_INFILE);
			break;
		}
		case 2:
		{
			dprintf(2, "token: %s\n", PRINT_HERE_DOC);
			break;
		}
		case 3:
		{
			dprintf(2, "token: %s\n", PRINT_OUTFILE);
			break;
		}
		case 4:
		{
			dprintf(2, "token: %s\n", PRINT_OUTFILE_APPEND);
			break;
		}

		default:
			break;
	}
}
//du coup j'ai la fonction lexer. j'arrive a creer une liste chainee. j'arrive a rentrer le token et la string de l commende mais je fait 0 check si l'argument que je rentre dans ma liste chainee est valide
void	print_lexer(t_lexer **lexer)
{
	t_lexer *tmp;

	tmp = *lexer;
	while (tmp)
	{
		debugToken(tmp->token);
		tmp = tmp->next;
	}
}

bool	check_token(int i, char *str)
{
	if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		return (true);
	return (false);
}


int	build_token(int i, char *str, t_data *data)
{
	t_lexer	*tmp;

	if (str[i] == '|')
	{
		tmp = ft_lexer_new(NULL, PIPE, 0);
		ft_lexer_add_back(&data->lexer, tmp);
		i++;
	}
	else if (str[i] == '<')
	{
		if (str[i + 1] == '<')
		{
			tmp = ft_lexer_new(NULL, HERE_DOC, 0);
			ft_lexer_add_back(&data->lexer, tmp);
			i += 2;
		}
		else
		{
			tmp = ft_lexer_new(NULL, INFILE, 0);
			ft_lexer_add_back(&data->lexer, tmp);
			i++;
		}
	}
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
		{
			tmp = ft_lexer_new(NULL, OUTFILE_APPEND, 0);
			ft_lexer_add_back(&data->lexer, tmp);
			i += 2;
		}
		else
		{
			tmp = ft_lexer_new(NULL, OUTFILE, 0);
			ft_lexer_add_back(&data->lexer, tmp);
			i++;
		}
	}
	return (i);
}

int	skipe_space(int	i, char *str)
{
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

void	lexer(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i] != '\0')
	{
		if (data->input[i] == ' ')
			i = skipe_space(i, data->input);
		if (check_token(i, data->input) == true)
			i = build_token(i, data->input, data);
		else
			i = build_cmd(i, data->input, data);
	}
	print_lexer(&data->lexer);
//	ft_lexer_clear(&data->lexer);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_env	*tmp;
	int	i;

//	env[0] = NULL;
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
	i = -1;
	if (data.path)
	{
		while (data.path[++i])
			printf("path_line[%d] : %s\n", i, data.path[i]);
//		ft_free_split(&data);
	}
	while (1)
	{
		data.input = readline("Minishell > ");
		add_history(data.input);
		lexer(&data);
		//dprintf(2, "|%s|\n", data.input);
		free (data.input);
	}
	ft_env_clear(&data.env);
}
