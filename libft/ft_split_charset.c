/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 21:11:29 by ede-thom          #+#    #+#             */
/*   Updated: 2021/05/29 22:10:34 by ede-thom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	word_count(char *str, char *charset)
{
	int	n;
	int	i;

	n = 0;
	i = -1;
	while (str[++i])
	{
		if (ft_indexof(str[i], charset) == -1)
		{
			while (ft_indexof(str[i], charset) == -1 && str[i])
			{
				i++;
			}
			n++;
			if (!str[i])
				return (n);
		}
	}
	return (n);
}

static int	word_length(char *start, char *charset)
{
	int	i;

	i = 0;
	while (start[i] && ft_indexof(start[i], charset) == -1)
		i++;
	return (i);
}

static char	**init(int *word, int *i, char *s, char *cs)
{
	char	**splut;

	if (s == NULL || cs == NULL)
		return ((char **) NULL);
	*word = -1;
	*i = 0;
	splut = (char **)malloc(sizeof(char *) * (word_count(s, cs) + 1));
	if (!splut)
		return (0);
	return (splut);
}

static void	auxsplut(int len, int i, char *splut_at_word, char *str)
{
	int	j;

	j = -1;
	while (++j < len)
		splut_at_word[j] = str[i + j];
	splut_at_word[j] = '\0';
}

char	**ft_split_charset(char *str, char *charset)
{
	int		i;
	int		word;
	int		len;
	char	**splut;

	splut = init(&word, &i, str, charset);
	if (!splut)
		return (NULL);
	while (++word < word_count(str, charset))
	{
		while (ft_indexof(str[i], charset) != -1)
			i++;
		len = word_length(&str[i], charset);
		if (len >= 0)
		{
			splut[word] = (char *)malloc(sizeof(char) * (len + 1));
			if (!splut[word])
				return (NULL);
			auxsplut(len, i, splut[word], str);
		}
		i += len;
	}
	splut[word_count(str, charset)] = 0;
	return (splut);
}
