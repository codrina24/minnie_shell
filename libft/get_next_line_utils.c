/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:55:36 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/13 12:30:36 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_next(char *str)
{
	size_t	i;

	if (str == NULL)
		return (-1);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr_next(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	if ((char)c == '\0')
	{
		return ((char *)&s[i]);
	}
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	return (0);
}

char	*ft_strjoin_next(char *s1, char *s2)
{
	size_t	i;
	size_t	y;
	size_t	len;
	char	*join;

	i = 0;
	y = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen_next(s1) + ft_strlen_next(s2);
	join = malloc(sizeof(char) * (len + 1));
	if (!join)
		return (NULL);
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[y] != '\0')
	{
		join[i + y] = s2[y];
		y++;
	}
	join[i + y] = '\0';
	return (join);
}

char	*ft_strdup_next(char *s)
{
	char	*duplicate;
	size_t	i;

	i = 0;
	duplicate = (char *)malloc((sizeof(char)) * (ft_strlen_next(s) + 1));
	if (!duplicate)
		return (NULL);
	while (s[i] != '\0' || i < ft_strlen_next(s))
	{
		duplicate[i] = s[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

char	*ft_substr_next(char *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	lens;
	size_t	i;
	size_t	x;

	i = 0;
	x = start;
	lens = ft_strlen_next(s);
	if (!s)
		return (NULL);
	if (x >= lens)
		return (ft_strdup_next(""));
	if (len > lens - start)
		len = lens - start;
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (i < len && x < lens)
	{
		new[i] = s[x];
		i++;
		x++;
	}
	new[i] = '\0';
	return (new);
}
