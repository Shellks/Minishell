/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:16:44 by nibernar          #+#    #+#             */
/*   Updated: 2023/07/20 14:58:16 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static int	ft_len(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static char	*ft_word(char *str, char c)
{
	size_t	i;
	size_t	len;
	char	*word;

	i = 0;
	len = ft_len(str, c);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_splitter(char **strs, char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s != 0)
		{
			strs[i] = ft_word(s, c);
			if (strs[i] == NULL)
			{
				while (i >= 0)
					free(strs[i--]);
				free(strs);
				return (NULL);
			}
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	strs[i] = 0;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	char	*ptr;

	ptr = (char *)s;
	str = malloc(sizeof(char *) * (ft_count(ptr, c) + 1));
	if (!(str) || ptr == 0)
		return (NULL);
	return (ft_splitter(str, (char *)s, c));
}
