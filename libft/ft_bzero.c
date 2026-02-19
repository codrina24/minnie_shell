/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:28:59 by coholbur          #+#    #+#             */
/*   Updated: 2024/11/29 14:53:58 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*a;
	size_t			i;

	a = s;
	i = 0;
	while (i < n)
	{
		a[i] = '\0';
		i++;
	}
}

// int	main(void)
// {
// 	char str[10] = "abcdefghij";
// 	printf("%s\n", str);
// 	ft_bzero(str, 8);
// 	printf("%s\n", str);
// 	return (0);
// }
