/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:59:56 by coholbur          #+#    #+#             */
/*   Updated: 2025/06/24 17:15:51 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	y;
	size_t	len;
	char	*join;

	i = 0;
	y = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc((len + 1) * sizeof(char));
	if (!join)
		return (NULL);
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	y = 0;
	while (s2[y] != '\0')
		join[i++] = s2[y++];
	join[i] = '\0';
	return (join);
	free (join);
}
/*
#include <stdio.h>

int	main(void)
{
	char	str1[] = "abc";
	char	str2[] = "ddd";
	char	*joinnn;

	joinnn = ft_strjoin(str1, str2);
	printf("%s\n", joinnn);
	return (0);
} */
