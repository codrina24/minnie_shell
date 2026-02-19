/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:51:11 by coholbur          #+#    #+#             */
/*   Updated: 2024/11/18 11:07:10 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
/*
int	main(void)
{
	int c;

	c = 61;
	printf("%i\n", ft_isalpha(c));

	
	c = 97;
	prntf("%i\n", isalpha(c));

	c = 58;
	printf("%i\n", isalpha(c));

	return(0);
} */
