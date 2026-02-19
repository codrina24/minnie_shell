/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coholbur <coholbur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:57:39 by coholbur          #+#    #+#             */
/*   Updated: 2025/09/13 12:15:05 by coholbur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int content)
{
	t_list	*src;

	src = (t_list *)malloc(sizeof(t_list));
	if (!src)
		return (NULL);
	src->content = content;
	src->next = NULL;
	return (src);
}
