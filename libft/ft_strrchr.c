/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:13:03 by coholbur          #+#    #+#             */
/*   Updated: 2024/11/29 14:55:21 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include   "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == ((char)c))
			return ((char *)&s[len]);
		len--;
	}
	if (s[len] == c)
		return ((char *)&s[len]);
	return (NULL);
}
/*
// int main(void)
// {
//     const char src[] = "hellex";
//     int e;

//     e = 'e';
//     printf("%p\n", ft_strrchr(src, '5'));
    
//     printf("%p\n", strrchr(src, '5'));
//     return (0);
// } */
