/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:29:16 by coholbur          #+#    #+#             */
/*   Updated: 2024/11/29 12:30:23 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char				temp;
	char				*a;
	const char			*b;
	size_t				i;

	i = 0;
	a = dest;
	b = src;
	if (a == NULL && b == NULL)
		return (NULL);
	while (a < b && i < n)
	{
		temp = b[i];
		a[i] = temp;
		i++;
	}
	while (a > b && n > 0)
	{
		n--;
		temp = b[n];
		a[n] = temp;
	}			
	return (dest);
}
/* int	main(void)
// {
// 	char	src[] = "123456789";
//   src = 123453459
//   dest =   453459
// 	=
  
//   src = 1231 56789
//   dest =   156789

//  	src = 12312345
//   dest = 12345  */
// 	unsigned char	dest[10];
// 	ft_memmove(src+4, src, 2147483640);
// 	//memmove(src+4, src, 7);
// 	printf("memmove %s\n", src + 3);
// 	printf("ft_memmove %s\n", src+3);

// } */
