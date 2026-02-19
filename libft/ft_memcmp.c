/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:50:54 by coholbur          #+#    #+#             */
/*   Updated: 2024/11/29 13:09:20 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned char		*stra;
	unsigned char		*strb;

	stra = (unsigned char *)s1;
	strb = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (stra[i] != strb[i])
			return (stra[i] - strb[i]);
		i++;
	}
	return (0);
}
/*    //if (ss[i] != sss[i])
	//	return (ss[i] - sss[i]);
	return (0);
}
int main(void)
{
    const unsigned char str[] = "s";
    const unsigned char str2[] = "sal";
    //if (ac == 4)
    printf("%d\n", ft_memcmp(str, str2, 4));
    printf("%d\n", memcmp(str, str2, 4));
   return (0); 
}
*/
