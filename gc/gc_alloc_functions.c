/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_alloc_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzerad <mzerad@student.42.fr>     	        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:46:03 by mzerad            #+#    #+#             */
/*   Updated: 2025/06/24 18:11:03 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

char	*ft_gc_strdup(t_gc *gc, const char *s)
{
	size_t	len;
	char	*copy;

	if (!gc || !s)
		return (NULL);
	len = ft_strlen(s) + 1;
	copy = ft_gc_malloc(gc, len);
	if (!copy)
		return (NULL);
	ft_memcpy(copy, s, len);
	return (copy);
}

char	*ft_gc_substr(t_gc *gc, const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*substr;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_gc_strdup(gc, ""));
	if (len > s_len - start)
		len = s_len - start;
	substr = ft_gc_malloc(gc, len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_gc_strjoin(t_gc *gc, const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = ft_gc_malloc(gc, s1_len + s2_len + 1);
	if (!join)
		return (NULL);
	ft_memcpy(join, s1, s1_len);
	ft_memcpy(join + s1_len, s2, s2_len + 1);
	return (join);
}

char	*ft_gc_strjoin_cmd(t_gc *gc, const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = ft_gc_malloc(gc, s1_len + s2_len + 2);
	if (!join)
		return (NULL);
	ft_memcpy(join, s1, s1_len);
	ft_strcat(join, "/");
	ft_memcpy(join + s1_len + 1, s2, s2_len + 1);
	return (join);
}

char	*ft_gc_itoa(t_gc *gc, int nbr)
{
	char	*result;
	int		size;
	long	n;

	n = nbr;
	size = ft_count_char_in_nbr(n);
	result = ft_gc_malloc(gc, sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result[size] = '\0';
	if (n == 0)
		return (result[0] = '0', result);
	if (n < 0)
	{
		result[0] = '-';
		n = -n;
	}
	while (n)
	{
		result[--size] = n % 10 + '0';
		n /= 10;
	}
	return (result);
}
