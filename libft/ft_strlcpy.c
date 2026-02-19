/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:14:38 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/13 12:27:40 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"	

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (n == 0)
		return (len);
	while (src[i] && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}

/*int	main(void)
{
	char dest[5];
	char dst[5];
	const char src[] = "lorem ipsum";
	ft_strlcpy(dest, src, 1);
	printf("%zu\n", ft_strlen(src));
	printf("%s\n", dest);
	strlcpy (dst, src, 1);
	printf("vrai :" "%zu\n", ft_strlen(src)); 
	printf("%s\n", dst);
	return (0);
}*/
