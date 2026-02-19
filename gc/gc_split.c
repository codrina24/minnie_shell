/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_init_track_and_malloc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzerad <mzerad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:46:03 by mzerad            #+#    #+#             */
/*   Updated: 2025/08/07 15:08:26 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

static size_t	ft_count_words(const char *str, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if ((i == 0 || str[i - 1] == c) && str[i] != c)
			count++;
		i++;
	}
	return (count);
}

static size_t	ft_skip_c(const char *s, char c, size_t i)
{
	while (s[i] == c)
		i++;
	return (i);
}

static char	*ft_extract_word(t_gc *gc, const char *s, char c, size_t *i)
{
	size_t	start;

	start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	if (*i > start)
		return (ft_gc_substr(gc, s, start, *i - start));
	return (NULL);
}

static void	ft_free_split_tab(t_gc *gc, char **tab, size_t n)
{
	while (n > 0)
		ft_gc_free_one(gc, tab[--n]);
	ft_gc_free_one(gc, tab);
}

char	**ft_gc_split(t_gc *gc, const char *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	n;
	size_t	len;

	if (!s)
		return (NULL);
	i = 0;
	n = 0;
	len = ft_count_words(s, c);
	tab = ft_gc_malloc(gc, sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	while (s[i] && n < len)
	{
		i = ft_skip_c(s, c, i);
		tab[n] = ft_extract_word(gc, s, c, &i);
		if (tab[n] == NULL)
			return (ft_free_split_tab(gc, tab, n), NULL);
		n++;
	}
	tab[n] = NULL;
	return (tab);
}	

/*
char	**ft_gc_split(t_gc *gc, const char *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	n;
	size_t	start;
	size_t	len;

	if (!s)
		return (NULL);

	i = 0;
	n = 0;
	len = ft_count_words(s, c);
	tab = ft_gc_malloc(gc, sizeof(char*) * (len + 1));
	if (!tab)
		return (NULL);
	while (s[i] && n < len)
	{		
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		if (i > start)
		{
			tab[n] = ft_gc_substr(gc, s, start, i - start);
			if (!tab[n]) 
			{
				while (n > 0)
					ft_gc_free_one(gc, tab[--n]);
				ft_gc_free_one(gc, tab);
				return (NULL);
			}
			n++;
		}
	}
	tab[n] = NULL;
	return (tab);
}
*/
/*
int main()
{
	t_gc gc;
	char str[] = "Hello hi hello	my dear   ";
	char **split;
	int i;

	i = 0;
	split = ft_gc_split(&gc, str, ' ');
	if(!split)
		return(-1);
	while(split[i])
	{
		printf("%s\n", split[i]);
		free(split[i]);
		i++;
	}
	return(0);
} */
