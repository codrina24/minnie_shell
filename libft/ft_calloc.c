/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:32:27 by coholbur          #+#    #+#             */
/*   Updated: 2024/11/29 14:16:13 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	result;

	ptr = NULL;
	result = nmemb * size;
	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (size != 0 && nmemb > (2147483647 / size))
		return (NULL);
	ptr = malloc(result);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, result);
	return (ptr);
}
/*
int main(void)
{
    long *y;
    
    y = (long *)ft_calloc(10, sizeof(long *));
    //y = (long *)calloc(20, 555555555555555);

    if (y != NULL)
        printf("ok");
    else
        printf("ko");
    return (0);    
}
*/
