/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:05:10 by coholbur          #+#    #+#             */
/*   Updated: 2024/11/29 12:04:28 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*a;	
	unsigned char		b;

	a = s;
	b = c;
	i = 0;
	while (n--)
	{
		*&a[i] = b;
		i++;
	}
	return (a);
}
/*
int	main(void)
{
	char str[10] = "abcd";
	ft_memset(str, 'a', 3);
	printf("%s\n", str);
	memset(str, 'a', 3);

	printf("%s\n", str);
	return (0);
}
*/
