/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:05:30 by coholbur          #+#    #+#             */
/*   Updated: 2024/11/29 15:03:43 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	toupp(unsigned int i, char c)
// {
// 	i = 0;
// 	if (c >= 97 && c <= 122)

// 			c -= 32;
// 	return (c);
// }
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;
	size_t			taille;

	i = 0;
	if (!s || !f)
		return (NULL);
	taille = ft_strlen(s);
	str = (char *)malloc((sizeof(char) * (taille + 1)));
	if (!str)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
// int main(void)
// {
//     char str[] = "abc";
//     char *result;
//     result = ft_strmapi(str, toupp);
//     printf("%s\n", result);
//     return (0);
// }
