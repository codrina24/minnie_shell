/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:01:14 by coholbur          #+#    #+#             */
/*   Updated: 2024/11/29 14:29:46 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_substr(char const *s, unsigned int start,
size_t len)
{
	char	*new;
	size_t	lens;
	size_t	i;
	size_t	x;

	i = 0;
	x = start;
	lens = ft_strlen(s);
	if (!s)
		return (NULL);
	if (x >= lens)
		return (ft_strdup(""));
	if (len > lens - start)
		len = lens - start;
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (i < len && x < lens)
	{
		new[i] = s[x];
		i++;
		x++;
	}
	new[i] = '\0';
	return (new);
}
/*  
// int main(void)
// {
//     char str[] = "abcd";
//     ft_substr(str, 3, 6);
//     printf("%s\n", str);      
// } */
