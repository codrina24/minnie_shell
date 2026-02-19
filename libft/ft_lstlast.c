/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:00:20 by coholbur          #+#    #+#             */
/*   Updated: 2025/03/19 18:27:46 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	if (lst == 0)
		return (lst);
	while (lst)
	{
		last = lst;
		lst = lst->next;
	}
	return (last);
}
/*
int	main(void)
{
t_list	*src;

src = (t_list *)malloc(sizeof(t_list));
src->content = (char *)"abc";
src->next = NULL;
printf("%s\n", (char *)ft_lstlast(src));
return (0);
}
*/