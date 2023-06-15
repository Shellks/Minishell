/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:16:44 by nibernar          #+#    #+#             */
/*   Updated: 2023/06/15 10:44:27 by acarlott         ###   ########lyon.fr   */
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

// static int	ft_free_malloc(char **words_tab, int i)
// {
// 	if (!words_tab[i])
// 	{
// 		while (i >= 0)
// 		{
// 			free(words_tab[i]);
// 			i--;
// 		}
// 		free(words_tab);
// 		return (1);
// 	}
// 	return (0);
// }

// static int	ft_words_size(char const *s, char c)
// {
// 	int	i;
// 	int	words_size;

// 	i = 0;
// 	words_size = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == c)
// 		{
// 			while (s[i] == c)
// 			i++;
// 		}
// 		if (s[i] == '\0')
// 			break ;
// 		while (s[i] && s[i] != c)
// 			i++;
// 		words_size++;
// 	}
// 	return (words_size);
// }

// static char	**ft_split_bis(const char *s, char **words_tab, char c, int i)
// {
// 	int	index;
// 	int	j;

// 	index = 0;
// 	j = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == c)
// 		{
// 			while (s[i] == c)
// 				i++;
// 		}
// 		if (s[i] == '\0')
// 			break ;
// 		index = i;
// 		while (s[index] && s[index] != c)
// 			index++;
// 		words_tab[j] = ft_substr(s, i, (index - i));
// 		if (j <= ft_words_size(s, c) && ft_free_malloc(words_tab, j))
// 			return (0);
// 		j++;
// 		i = index;
// 	}
// 	return (words_tab);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**words_tab;

// 	if (!s)
// 		return (0);
// 	printf("%s\n", s);
// 	words_tab = ft_calloc(sizeof(char *), (ft_words_size(s, c) + 1));
// 	if (!words_tab)
// 		return (0);
// 	return (ft_split_bis(s, words_tab, c, 0));
// }
