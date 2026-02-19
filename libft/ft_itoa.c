/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:48:25 by coholbur          #+#    #+#             */
/*   Updated: 2024/12/03 16:32:25 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_char_in_nbr(long n)
{
	int			i;
	long int	nbr;

	i = 0;
	nbr = (long int)n;
	if (!nbr)
		return (1);
	if (nbr < 0)
	{
		nbr = nbr * -1;
		i++;
	}
	while (nbr > 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	nbr;
	int			i;

	nbr = (long int)n;
	i = ft_count_char_in_nbr(n);
	str = (char *)malloc((sizeof(char) * (i + 1)));
	if (!str)
		return (NULL);
	if (nbr == 0)
	{
		str[0] = '0';
	}
	if (nbr < 0)
	{
		nbr = nbr * -1;
		str[0] = '-';
	}
	str[i] = '\0';
	while (nbr > 0 && i--)
	{
		str[i] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (str);
}
/*
// int	main(void)
// {
//     int num1;
//     char *a;

//     num1 = 2147483647;
// 	a = ft_itoa(num1);
// 	printf("%s\n", a);
// 	return (0);
// }
*/
