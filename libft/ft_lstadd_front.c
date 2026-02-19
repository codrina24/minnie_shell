/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:31:15 by coholbur          #+#    #+#             */
/*   Updated: 2025/02/25 20:22:22 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

/*
// int main(void)
// {
//     t_list *node1;
//     t_list *node2;
//     t_list *nodenewone;

//     (intptr_t)
//     node2 = (t_list *)malloc(sizeof(t_list));
//     nodenewone = (t_list *)malloc(sizeof(t_list));

//     node1->content = (void *)42;
//     node1->next = node2;
//     node2->content = (void *)5;
//     node2->next = NULL;

//     printf("%d->%d\n", (int)(intptr_t)node1->content,
//     (int)(intptr_t)node2->content);

//     nodenewone->content = (void *)100;
//     nodenewone->next = NULL;

//     ft_lstadd_front(&node1, nodenewone);

//     printf("%d->%d->%d\n", (int)(intptr_t)nodenewone->content,
//     (int)(intptr_t)node1->content,
//     (int)(intptr_t)node2->content);

//     return(0);
// }
*/
