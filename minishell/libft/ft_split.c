/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: authomas <authomas@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:01:20 by authomas          #+#    #+#             */
/*   Updated: 2025/06/14 13:54:16 by authomas         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char *str, char charset)
{
	size_t	i;
	size_t	nbr_word;
	int		new_word;

	i = 0;
	nbr_word = 0;
	new_word = 1;
	while (str[i])
	{
		if (new_word && str[i] != charset)
		{
			nbr_word++;
			new_word = 0;
		}
		if (str[i] == charset)
			new_word = 1;
		i++;
	}
	return (nbr_word);
}

static size_t	word_len(char *str, char charset)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != charset)
		i++;
	return (i);
}

static int	fill_words(char **words, char *str, char charset, size_t nbr_word)
{
	size_t	j;
	size_t	k;
	size_t	len_word;

	j = 0;
	while (j < nbr_word)
	{
		k = 0;
		while (str && *str == charset)
			str++;
		len_word = word_len(str, charset);
		words[j] = malloc(sizeof(char) * (len_word + 1));
		if (!words[j])
			return (0);
		while (k < len_word)
		{
			words[j][k] = *str;
			str++;
			k++;
		}
		words[j][k] = '\0';
		j++;
	}
	words[j] = NULL;
	return (1);
}

static void	free_split(char **words)
{
	size_t	i;

	i = 0;
	while (words && words[i])
	{
		if (words[i])
		{
			free(words[i++]);
			words[i - 1] = NULL;
		}
	}
	if (words)
		free(words);
}

char	**ft_split(char *str, char charset)
{
	char	**words;
	size_t	nbr_word;

	if (!str)
		return (NULL);
	nbr_word = count_words(str, charset);
	words = ft_calloc((nbr_word + 1), sizeof(char *));
	if (!words)
		return (NULL);
	if (!fill_words(words, str, charset, nbr_word))
	{
		free_split(words);
		return (NULL);
	}
	return (words);
}
