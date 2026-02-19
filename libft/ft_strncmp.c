/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:20:18 by coholbur          #+#    #+#             */
/*   Updated: 2024/11/29 15:02:33 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
		i++;
	return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
}
/*
// int main(void)
//  {
//  	unsigned int n = 4;
//      char str[] = "test";
//      char str2[] = "test";
//      printf("%d\n", ft_strncmp(str, str2, n));
//      printf("%d\n", strncmp(str, str2, n));
//     return (0);
//  }
*/
