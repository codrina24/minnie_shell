/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:37:47 by coholbur          #+#    #+#             */
/*   Updated: 2024/11/29 12:12:42 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char			*a;
	const unsigned char		*b;
	size_t					i;

	a = dest;
	b = src;
	i = 0;
	if (a == NULL && b == NULL)
		return (NULL);
	while (n--)
	{
		a[i] = b[i];
		i++;
	}			
	return (dest);
}

// int	main(void)
// {
// 	char	src[] = "";
// 	unsigned char dest[4] = "";
// 	ft_memcpy(dest, src, 4);
// 	printf("%s\n", (unsigned char *)&dest);
// 	memcpy(dest, src, 4);
// 	printf("%s\n", (unsigned char *)&dest);
// 	return (0); 
// }
