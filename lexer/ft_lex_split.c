/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lex_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzerad <mzerad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:36:40 by mzerad            #+#    #+#             */
/*   Updated: 2025/09/27 18:00:49 by mzerad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../parser/pars_minishell.h"

int	ft_count_segments(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		count++;
		while (s[i])
		{
			if (s[i] == c && !ft_is_in_quotes(s, i))
				break ;
			i++;
		}
	}
	if (count < 0)
		count = 0;
	return (count);
}

int	ft_split_process(const char *s, char c, int *i)
{
	int	start;

	if (!s)
		return (-1);
	while (s[*i] == c)
		(*i)++;
	if (!s[*i])
		return (0);
	start = *i;
	while (s[*i])
	{
		if (s[*i] == c && !ft_is_in_quotes(s, *i))
			break ;
		(*i)++;
	}
	return (*i - start);
}

int	ft_lex_split_process(char **tab, char *s, char c, t_gc *gc)
{
	int		i;
	int		n;
	int		segment;
	char	*temp;

	i = 0;
	n = 0;
	while (1)
	{
		segment = ft_split_process(s, c, &i);
		if (segment <= 0)
			break ;
		temp = ft_gc_substr(gc, s, i - segment, segment);
		if (!temp)
			return (-1);
		tab[n++] = temp;
	}
	tab[n] = NULL;
	return (0);
}

char	**ft_lex_split(char *s, char c, t_gc *gc)
{
	char	**tab;
	int		count;

	if (!s || !gc)
		return (NULL);
	count = ft_count_segments(s, c);
	if (count <= 0)
		return (NULL);
	tab = (char **)ft_gc_malloc(gc, sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	if (ft_lex_split_process(tab, s, c, gc) < 0)
		return (ft_gc_free_tab(gc, tab), NULL);
	return (tab);
}
