/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:32:59 by coholbur          #+#    #+#             */
/*   Updated: 2024/12/03 14:14:02 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst == 0 || new == 0)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}
/*
//     int main(void)
// {
//     t_list *node1;
//     t_list *node2;
//     t_list *nodenewone;

//     node1 = (t_list *)malloc(sizeof(t_list));
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

//     ft_lstadd_back(&node2, nodenewone);

//     printf("%d->%d->%d\n", (int)(intptr_t)nodenewone->content,
//     (int)(intptr_t)node2->content,
//     (int)(intptr_t)node1->content);

//     return(0);
// }
*/