/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:17:50 by coholbur          #+#    #+#             */
/*   Updated: 2024/11/29 12:38:59 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"	

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}
/*
int	main(void)
{
	int c;
	c = 'b';
	printf("%c\n", ft_toupper(c));
	toupper(c);
	printf("%c\n", c);
 	return (0);
}
*/
