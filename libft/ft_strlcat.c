/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:51:42 by coholbur          #+#    #+#             */
/*   Updated: 2024/11/29 12:37:51 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include	"libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	lendest;
	size_t	lensrc;

	lendest = ft_strlen(dest);
	lensrc = ft_strlen(src);
	i = 0;
	if (n <= lendest)
		return (n + lensrc);
	while (src[i] && i < n - 1 - lendest)
	{
		dest[lendest + i] = src[i];
		i++;
	}
	dest[lendest + i] = '\0';
	return (lendest + lensrc);
}
/*
int main(void)
{
    char dest[10] = "a";
    char src[] = "abcd";
    ft_strlcat(dest, src, 8);
    printf("%s\n", dest);
    strlcat(dest, src, 8);
    printf("%s\n", dest);
    return(0);
}
*/
