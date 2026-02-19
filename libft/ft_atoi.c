/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:26:30 by coholbur          #+#    #+#             */
/*   Updated: 2024/11/29 14:54:07 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	signe;
	int	result;

	i = 0;
	signe = 1;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	while (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
		{
			signe *= -1;
		}
		i++;
		if (nptr[i] == '-' || nptr[i] == '+')
			return (0);
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		result = 10 * result + (nptr[i] - '0');
		i++;
	}
	return (signe * result);
}
/*
// int	main(void)
// {
// 	const char	num[] = "--54";

// 	printf("%d\n", ft_atoi(num));
// 	printf("%d\n", atoi(num));
// 	return (0);
// } */
