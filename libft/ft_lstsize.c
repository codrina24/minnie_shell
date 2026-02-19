/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:28:26 by coholbur          #+#    #+#             */
/*   Updated: 2024/12/03 14:16:16 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
/*
// int main(void)
// {
//     t_list *src;

//     src = (t_list *)malloc(sizeof(t_list));

//     src->content = (void *)2455;
//     src->next = NULL;

//     printf("%d\n", ft_lstsize(src));
//     return (0);
// }
*/
