/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:40:35 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/13 12:29:58 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	first;
	size_t	last;

	if (!s1 || !set)
		return (NULL);
	first = 0;
	last = ft_strlen(s1);
	while (ft_strchr(set, s1[first]))
	{
		first++;
	}
	while (ft_strchr(set, s1[last]))
	{
		last--;
	}
	new = ft_substr(s1, first, (last - first + 1));
	return (new);
}
/*
#include <stdio.h>

 int main(void)
{
	char all[] = "\\aab\\bbaa\\";
		char search[] = "D";
		char *new;
		new = ft_strtrim(all, search);
		printf("%s\n", new);
	return (0);
 }
*/
