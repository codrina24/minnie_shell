/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:46:38 by coholbur          #+#    #+#             */
/*   Updated: 2024/11/29 12:00:11 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

int	ft_isalnum(int c)
{
	unsigned char	x;

	x = c;
	if ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z')
		|| (x >= '0' && x <= '9'))
		return (1);
	return (0);
}
/*

int	main(void)
{
	unsigned char y;

	y = 'o';
	printf("%d\n", ft_isalnum(y));

	return(0);
} 
*/
