/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:50:16 by coholbur          #+#    #+#             */
/*   Updated: 2024/11/29 12:53:26 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*str;
	unsigned char		d;

	d = c;
	i = 0;
	str = s;
	while (i < n)
	{
		if (str[i] == d)
		{	
			return ((unsigned char *)&str[i]);
		}
		i++;
	}	
	return (NULL);
}
/*
int main(void)
{
    const void *yy;
	
	yy = "abcd";
    int y;
    y = 'a';	
	ft_memchr(yy,y, 5);
    printf("%s\n", (char *)yy);
	printf("%s\n", (char *)memchr(yy, y, 5));

    return (0);
}

*/
