/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:41:44 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/13 12:25:03 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_words(const char *str, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if ((i == 0 || str[i -1] == c) && str[i] != c)
			count++;
	i++;
	}
	return (count);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	n;
	size_t	start;

	i = 0;
	n = 0;
	tab = (char **)malloc(sizeof(char *) * ((count_words(s, c)) + 1));
	if (!tab)
		return (NULL);
	while (s[i] && n < count_words(s, c))
	{		
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i])
		i++;
		if (i > start)
		{
			tab[n] = ft_substr(s, start, i - start);
			n++;
		}
	}
	tab[n] = NULL;
	return (tab);
}
